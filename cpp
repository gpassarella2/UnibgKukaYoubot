/********************************************************************************
 *
 * VelocityController.cpp
 *
 ******************************************************************************
 */
#include "VelocityController.hpp"
#include <iostream>
#include <sstream>

#include <cmath> 
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>

using namespace stresa;

namespace aurora {
namespace components {

// Variabili per gestire la logica di movimento
static double start_x_s = 0.0;
static double start_y_s = 0.0;
static double start_th_s = 0.0;
static bool executing_motion = false;

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
    
    // Distanza globale dal target
    double dx_global = target_x - current_x;
    double dy_global = target_y - current_y;
    double rho = std::sqrt(dx_global*dx_global + dy_global*dy_global);

    // STOP Condition
    if (rho < 0.1) {
        twist_vx = 0.0;
        twist_vy = 0.0;
        twist_wz = 0.0;
        goal_reached = true;
        manual_drive = true;
        executing_motion = false;
        std::cout << ">>> ARRIVATI A (-5, 11)! <<<" << std::endl;
        return;
    }
    
    // --- 1. GESTIONE TRASLAZIONE (Straight Line) ---
    // Per non fare un arco, calcoliamo il vettore nel mondo e lo ruotiamo
    // nel frame del robot. Il robot scivolerà dritto indipendentemente da come gira.
    
    double k_v = 0.6; // Velocità lineare
    
    // Proiezione vettoriale perfetta:
    // Vx e Vy sono calcolati istante per istante usando l'angolo CORRENTE del robot.
    // Questo compensa esattamente la rotazione del corpo.
    double cmd_vx = k_v * (dx_global * std::cos(current_theta) + dy_global * std::sin(current_theta));
    double cmd_vy = k_v * (-dx_global * std::sin(current_theta) + dy_global * std::cos(current_theta));

    // Saturazione lineare
    if (cmd_vx > 0.6) cmd_vx = 0.6;
    if (cmd_vx < -0.6) cmd_vx = -0.6;
    if (cmd_vy > 0.6) cmd_vy = 0.6;
    if (cmd_vy < -0.6) cmd_vy = -0.6;


    // --- 2. GESTIONE ROTAZIONE (Su se stesso) ---
    // Calcoliamo la percentuale di percorso fatto per interpolare la rotazione
    double total_dist = std::sqrt(std::pow(target_x - start_x_s, 2) + std::pow(target_y - start_y_s, 2));
    double progress = 1.0 - (rho / total_dist); 
    if(progress < 0) progress = 0; if(progress > 1) progress = 1;

    // Angolo desiderato ORA: parte da StartTheta e va verso TargetTheta linearmente
    // "Rotazione su se stesso" = rotazione attorno all'asse Z del robot (wz)
    double target_rotation_amount = M_PI / 2.0; // 90 gradi
    double desired_theta_now = start_th_s + (target_rotation_amount * progress);
    
    double theta_err = normalizeAngle(desired_theta_now - current_theta);
    double k_w = 2.0; // Alto guadagno per tenere l'angolo "incollato" all'interpolazione
    double cmd_wz = k_w * theta_err;

    // Saturazione angolare
    if (cmd_wz > 0.8) cmd_wz = 0.8;
    if (cmd_wz < -0.8) cmd_wz = -0.8;
    
    twist_vx = cmd_vx;
    twist_vy = cmd_vy;
    twist_wz = cmd_wz;
}

void VelocityController::task() {
    
    int key = _kbhit();
    if (key != -1) {
        readKeyboard(key); 
    }

    if (!manual_drive && !goal_reached) {
        runAutonomousControl(); 
    }

    geometry_msgs::msg::dds_::Twist_ twist_msg;
    twist_msg.linear().x(twist_vx);
    twist_msg.linear().y(twist_vy);     
    twist_msg.angular().z(twist_wz);
    twist_pub.publish(&twist_msg);

    odometryCallback(this);
}

void VelocityController::readKeyboard(int key) {

    if(key==8){
        std::cout << " : X +\n"; twist_vx += 0.1;
    } else if(key==2){
        std::cout << " : X -\n"; twist_vx -= 0.1;
    } else if(key==4){
        std::cout << " : Z +\n"; twist_wz += 0.1;
    } else if(key==6){
        std::cout << " : Z -\n"; twist_wz -= 0.1;
    } else if(key==0){
        std::cout << " : STOP\n";
        twist_vx = 0.0; twist_vy = 0.0; twist_wz = 0.0;
        manual_drive = true;
    } else if(key==7){
        std::cout << " : GOTO\n";
        twist_vx = 0.0; twist_vy = 0.0; twist_wz = 0.0;
        manual_drive = false;
    } else if(key==3){
        std::cout << "\n>>> TRASLAZIONE RETTILINEA + SPIN SU SE STESSO <<<\n";
        
        // Salvataggio start point per interpolazione corretta
        start_x_s = current_x;
        start_y_s = current_y;
        start_th_s = current_theta;

        target_x = -5.0;
        target_y = 11.0;
        
        // Target finale = Start + 90 gradi
        target_theta = normalizeAngle(start_th_s + (M_PI / 2.0)); 

        manual_drive = false;
        goal_reached = false;
        executing_motion = true;

        std::cout << "Start: (" << start_x_s << ", " << start_y_s << ")\n";
        std::cout << "Target: (" << target_x << ", " << target_y << ")\n";
    }
}

void VelocityController::init() { std::cout << "Init. Premi '3' per movimento." << std::endl; }
void VelocityController::reconfigure() {}
void VelocityController::skip() {}
void VelocityController::missed() {}
void VelocityController::quit() {}

void VelocityController::twistConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {}
void VelocityController::roverOdomConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {}

} // namespace components
} // namespace aurora
