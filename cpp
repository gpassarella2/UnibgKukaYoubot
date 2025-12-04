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

// Variabili per memorizzare lo stato iniziale e gestire l'interpolazione
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
    // ------------------------------------------------------------------
    // 1. CALCOLO DISTANZA GLOBALE (Il "Binario" su cui muoversi)
    // ------------------------------------------------------------------
    double dx_global = target_x - current_x;
    double dy_global = target_y - current_y;
    double dist_remaining = std::sqrt(dx_global*dx_global + dy_global*dy_global);

    // Stop condition
    if (dist_remaining < 0.05) {
        twist_vx = 0.0;
        twist_vy = 0.0;
        twist_wz = 0.0;
        goal_reached = true;
        manual_drive = true;
        motion_active = false;
        std::cout << ">>> TARGET RAGGIUNTO <<<" << std::endl;
        return;
    }

    // ------------------------------------------------------------------
    // 2. GESTIONE ROTAZIONE PROGRESSIVA (Come nelle foto)
    // ------------------------------------------------------------------
    // Calcoliamo quanto siamo distanti dall'inizio per decidere l'angolo attuale
    double dist_total_initial = std::sqrt(std::pow(target_x - start_x_s, 2) + std::pow(target_y - start_y_s, 2));
    
    // Percentuale completamento (0.0 -> 1.0)
    double progress = 0.0;
    if(dist_total_initial > 0.001) {
        progress = 1.0 - (dist_remaining / dist_total_initial);
    }
    if(progress < 0) progress = 0; if(progress > 1) progress = 1;

    // Angolo Target Variabile: Inizia a StartTheta, finisce a StartTheta+90°
    double rotation_span = M_PI / 2.0; // 90 gradi totali di rotazione
    double desired_heading_now = start_th_s + (rotation_span * progress);
    
    double theta_error = normalizeAngle(desired_heading_now - current_theta);
    
    // Controllo P semplice per la rotazione
    double k_w = 2.5; 
    double cmd_wz = k_w * theta_error;

    // ------------------------------------------------------------------
    // 3. CINEMATICA OLONOMICA (EVITA GLI ARCHI)
    // ------------------------------------------------------------------
    // Vogliamo andare dritti verso il target GLOBALE, indipendentemente dall'angolo robot.
    // Calcoliamo il vettore velocità nel mondo:
    double cruise_speed = 0.5; // m/s
    
    // Vettore unitario verso il target * velocità
    double v_world_x = (dx_global / dist_remaining) * cruise_speed;
    double v_world_y = (dy_global / dist_remaining) * cruise_speed;

    // TRASFORMAZIONE COORDINATE (Mondo -> Robot)     // Usiamo l'angolo CORRENTE del robot. Questo fa sì che se il robot ruota,
    // i motori compensano istantaneamente con Vy per mantenere la linea retta.
    double cos_th = std::cos(current_theta);
    double sin_th = std::sin(current_theta);

    double cmd_vx =  v_world_x * cos_th + v_world_y * sin_th;
    double cmd_vy = -v_world_x * sin_th + v_world_y * cos_th;

    // Limiti velocità
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
    twist_msg.linear().y(twist_vy); // NECESSARIO PER NON FARE ARCHI
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
        std::cout << "\n>>> START: Linea retta verso (11,0) con rotazione 90° <<<\n";
        
        // Salva posa iniziale (riferimento per l'interpolazione della rotazione)
        start_x_s = current_x;
        start_y_s = current_y;
        start_th_s = current_theta;

        // Imposta target: X=11, Y=0 (Come da tua richiesta precedente)
        target_x = 11.0;
        target_y = 0.0;
        
        // Target theta finale non viene usato direttamente nel loop (usiamo l'interpolazione)
        // ma concettualmente è start + 90°.
        target_theta = normalizeAngle(start_th_s + (M_PI / 2.0));

        manual_drive = false;
        goal_reached = false;
        motion_active = true;
    }
}

void VelocityController::init() { std::cout << "Init. Premi '3' per avvio." << std::endl; }
void VelocityController::reconfigure() {}
void VelocityController::skip() {}
void VelocityController::missed() {}
void VelocityController::quit() {}
void VelocityController::twistConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {}
void VelocityController::roverOdomConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {}

} // namespace components
} // namespace aurora
