/********************************************************************************
 * VelocityController.cpp
 ******************************************************************************/
#include "VelocityController.hpp"
#include <iostream>
#include <cmath> 
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>

using namespace stresa;

namespace aurora {
namespace components {

// Variabili statiche per memorizzare lo stato iniziale del movimento
static double start_x_s = 0.0;
static double start_y_s = 0.0;
static double start_th_s = 0.0;
static bool motion_active = false;

int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;
    if (!initialized) {
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }
    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    if (bytesWaiting == 0) return -1;
    return getchar() - 48; 
}

VelocityController::VelocityController() : VActivity() {
    registerPublisher(&twist_pub, "TwistPub", "rt/cmd_vel");
    registerSubscriber(&odometrySub, "OdometrySub", "rt/odom");

    twist_vx = 0.0;
    twist_vy = 0.0;
    twist_wz = 0.0;
    current_x = 0.0;
    current_y = 0.0;
    current_theta = 0.0;
    manual_drive = true;
    goal_reached = true;
}

VelocityController::~VelocityController() {}

double VelocityController::normalizeAngle(double angle) {
    while (angle > M_PI) angle -= 2.0 * M_PI;
    while (angle < -M_PI) angle += 2.0 * M_PI;
    return angle;
}

double VelocityController::quaternionToYaw(double x, double y, double z, double w) {
    double siny_cosp = 2.0 * (w * z + x * y);
    double cosy_cosp = 1.0 - 2.0 * (y * y + z * z);
    return std::atan2(siny_cosp, cosy_cosp);
}

void VelocityController::odometryCallback(VariantActivity* va) {
    VelocityController* activity = (VelocityController*) va;
    SampleInfo m_info;
    nav_msgs::msg::dds_::Odometry_ odo_msg;

    if(activity->odometrySub.takeNextData(&odo_msg, &m_info)) {
        activity->current_x = odo_msg.pose().pose().position().x();
        activity->current_y = odo_msg.pose().pose().position().y();
        
        double qx = odo_msg.pose().pose().orientation().x();
        double qy = odo_msg.pose().pose().orientation().y();
        double qz = odo_msg.pose().pose().orientation().z();
        double qw = odo_msg.pose().pose().orientation().w();
        
        activity->current_theta = activity->quaternionToYaw(qx, qy, qz, qw);
    }
}

void VelocityController::runAutonomousControl() {
    // 1. Calcolo vettore distanza GLOBALE (Mondo)
    double dx_global = target_x - current_x;
    double dy_global = target_y - current_y;
    double dist_remaining = std::sqrt(dx_global*dx_global + dy_global*dy_global);

    // Stop se arrivati (tolleranza 10 cm)
    if (dist_remaining < 0.10) {
        twist_vx = 0.0;
        twist_vy = 0.0;
        twist_wz = 0.0;
        goal_reached = true;
        manual_drive = true;
        motion_active = false;
        std::cout << ">>> TARGET RAGGIUNTO (11, 0) <<<" << std::endl;
        return;
    }

    // 2. Calcolo PROGRESSO (0.0 = inizio, 1.0 = arrivo)
    double dist_total = std::sqrt(std::pow(target_x - start_x_s, 2) + std::pow(target_y - start_y_s, 2));
    double fraction_done = 1.0 - (dist_remaining / dist_total);
    if(fraction_done < 0) fraction_done = 0;
    if(fraction_done > 1) fraction_done = 1;

    // 3. GESTIONE ROTAZIONE PROGRESSIVA
    // L'angolo target cambia man mano che avanzi.
    // Al 0% del percorso devi essere a StartTheta (es. 0°)
    // Al 100% del percorso devi essere a StartTheta + 90° (M_PI/2)
    double rotation_total_needed = M_PI / 2.0; [cite_start]// 90 gradi [cite: 1]
    double target_theta_now = start_th_s + (rotation_total_needed * fraction_done);
    
    double theta_error = normalizeAngle(target_theta_now - current_theta);
    double k_w = 2.0; // Guadagno rotazione
    double cmd_wz = k_w * theta_error;

    [cite_start]// 4. GESTIONE TRASLAZIONE VETTORIALE (Holonomic) [cite: 1]
    // Vogliamo andare dritti al target indipendentemente da come siamo girati.
    // Usiamo il vettore distanza globale e lo proiettiamo nel frame LOCALE.
    
    double v_cruise = 0.5; // Velocità di crociera m/s
    
    // Normalizziamo il vettore direzione globale e moltiplichiamo per velocità
    double v_global_x = v_cruise * (dx_global / dist_remaining);
    double v_global_y = v_cruise * (dy_global / dist_remaining);

    // Formule di rotazione inversa (da Mondo a Robot)
    // Vx_robot = Vgx * cos(th) + Vgy * sin(th)
    // Vy_robot = -Vgx * sin(th) + Vgy * cos(th)
    double cmd_vx = v_global_x * std::cos(current_theta) + v_global_y * std::sin(current_theta);
    double cmd_vy = -v_global_x * std::sin(current_theta) + v_global_y * std::cos(current_theta);

    // Saturazione comandi
    if (cmd_vx > 0.6) cmd_vx = 0.6;   if (cmd_vx < -0.6) cmd_vx = -0.6;
    if (cmd_vy > 0.6) cmd_vy = 0.6;   if (cmd_vy < -0.6) cmd_vy = -0.6;
    if (cmd_wz > 0.8) cmd_wz = 0.8;   if (cmd_wz < -0.8) cmd_wz = -0.8;
    
    twist_vx = cmd_vx;
    twist_vy = cmd_vy;
    twist_wz = cmd_wz;
}

void VelocityController::task() {
    int key = _kbhit();
    if (key != -1) readKeyboard(key); 

    if (!manual_drive && !goal_reached) {
        runAutonomousControl(); 
    }

    geometry_msgs::msg::dds_::Twist_ twist_msg;
    twist_msg.linear().x(twist_vx);
    twist_msg.linear().y(twist_vy); [cite_start]// Fondamentale per non fare archi [cite: 1]
    twist_msg.angular().z(twist_wz);
    twist_pub.publish(&twist_msg);

    odometryCallback(this);
}

void VelocityController::readKeyboard(int key) {
    if(key==8){ twist_vx += 0.1; std::cout << "X+\n"; }
    else if(key==2){ twist_vx -= 0.1; std::cout << "X-\n"; }
    else if(key==4){ twist_wz += 0.1; std::cout << "Z+\n"; }
    else if(key==6){ twist_wz -= 0.1; std::cout << "Z-\n"; }
    else if(key==0){ 
        twist_vx=0; twist_vy=0; twist_wz=0; 
        manual_drive=true; std::cout << "STOP\n"; 
    }
    else if(key==3){
        std::cout << "\n>>> AVVIO: Target (11,0) con rotazione graduale +90° <<<\n";
        
        // Salvataggio Start Point per calcolare la % di avanzamento
        start_x_s = current_x;
        start_y_s = current_y;
        start_th_s = current_theta;

        // Impostazione Target richiesto
        target_x = 11.0;
        target_y = 0.0;
        target_theta = normalizeAngle(start_th_s + (M_PI / 2.0)); // +90 gradi

        manual_drive = false;
        goal_reached = false;
        motion_active = true;
    }
}

void VelocityController::init() { std::cout << "Init. Premi '3' per test (11,0)." << std::endl; }
void VelocityController::reconfigure() {}
void VelocityController::skip() {}
void VelocityController::missed() {}
void VelocityController::quit() {}
void VelocityController::twistConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {}
void VelocityController::roverOdomConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {}

} // namespace components
} // namespace aurora
