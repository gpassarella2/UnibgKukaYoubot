/********************************************************************************
 *
 * VelocityController
 *
 * Copyright (c) 2019
 * All rights reserved.
 *
 * Davide Brugali, Università degli Studi di Bergamo
 *
 * -------------------------------------------------------------------------------
 * File: VelocityController.cpp
 * Created: May 5, 2019
 * Author: <A HREF="mailto:brugali@unibg.it">Davide Brugali</A>
 * -------------------------------------------------------------------------------
 *
 * This software is published under a dual-license: GNU Lesser General Public
 * License LGPL 2.1 and BSD license. The dual-license implies that users of this
 * code may choose which terms they prefer.
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

// --- Variabili di stato interne (non presenti nell'header hpp fornito) ---
static double current_x = 0.0;
static double current_y = 0.0;
static double current_theta = 0.0;

// Variabili per l'interpolazione del movimento (Start Point)
static double start_x_s = 0.0;
static double start_y_s = 0.0;
static double start_th_s = 0.0;

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
    return getchar() - 48; // Converte ASCII in intero
}

// Funzioni di utilità matematiche locali
double normalizeAngle(double angle) {
    while (angle > M_PI) angle -= 2.0 * M_PI;
    while (angle < -M_PI) angle += 2.0 * M_PI;
    return angle;
}

double quaternionToYaw(double x, double y, double z, double w) {
    double siny_cosp = 2.0 * (w * z + x * y);
    double cosy_cosp = 1.0 - 2.0 * (y * y + z * z);
    return std::atan2(siny_cosp, cosy_cosp);
}

VelocityController::VelocityController() : VActivity() {
    registerPublisher(&twist_pub, "TwistPub", "rt/cmd_vel");
    registerSubscriber(&odometrySub, "OdometrySub", "rt/odom");

    twist_vx = 0.0;
    twist_vy = 0.0;
    twist_wz = 0.0;

    target_x = 0.0;
    target_y = 0.0;
    target_theta = 0.0;

    manual_drive = true;
    goto_mode = false; 
}

VelocityController::~VelocityController() {}

void VelocityController::odometryCallback(VariantActivity* va) {
    VelocityController* activity = (VelocityController*) va;
    SampleInfo m_info;
    nav_msgs::msg::dds_::Odometry_ odo_msg;

    if(activity->odometrySub.takeNextData(&odo_msg, &m_info)) {
        // Aggiorniamo le variabili statiche locali
        current_x = odo_msg.pose().pose().position().x();
        current_y = odo_msg.pose().pose().position().y();
        
        double qx = odo_msg.pose().pose().orientation().x();
        double qy = odo_msg.pose().pose().orientation().y();
        double qz = odo_msg.pose().pose().orientation().z();
        double qw = odo_msg.pose().pose().orientation().w();
        
        current_theta = quaternionToYaw(qx, qy, qz, qw);
    }
}

// Logica di controllo Olonomico (Vx, Vy, Wz)
void VelocityController::task() {
    
    int key = _kbhit();
    if (key != -1) {
        readKeyboard(key); 
    }

    if (goto_mode && !manual_drive) {
        
        // 1. Calcolo Distanza Globale
        double dx_global = target_x - current_x;
        double dy_global = target_y - current_y;
        double dist_remaining = std::sqrt(dx_global*dx_global + dy_global*dy_global);

        // Controllo arrivo al target
        if (dist_remaining < 0.10) { // 10 cm tolleranza
            twist_vx = 0.0;
            twist_vy = 0.0;
            twist_wz = 0.0;
            manual_drive = true;
            goto_mode = false;
            std::cout << ">>> TARGET RAGGIUNTO (11, 0) <<<" << std::endl;
        } else {
            // 2. Calcolo percentuale avanzamento per rotazione graduale
            double total_path = std::sqrt(std::pow(target_x - start_x_s, 2) + std::pow(target_y - start_y_s, 2));
            double progress = 1.0;
            if (total_path > 0.001) {
                progress = 1.0 - (dist_remaining / total_path);
            }
            if (progress < 0.0) progress = 0.0;
            if (progress > 1.0) progress = 1.0;

            // 3. Interpolazione Rotazione: da StartTheta a StartTheta + 90°
            double rotation_span = M_PI / 2.0; // 90 gradi
            double desired_heading_now = start_th_s + (rotation_span * progress);
            double theta_error = normalizeAngle(desired_heading_now - current_theta);

            // Guadagno rotazione
            double k_w = 2.0;
            double cmd_wz = k_w * theta_error;

            // 4. Calcolo Velocità Vettoriale (No Archi)
            // Vogliamo muoverci dritti nel mondo, indipendentemente dall'angolo robot
            double cruise_speed = 0.5;
            
            // Vettore velocità desiderato nel MONDO
            double v_world_x = (dx_global / dist_remaining) * cruise_speed;
            double v_world_y = (dy_global / dist_remaining) * cruise_speed;

            // Trasformazione coordinate: Mondo -> Robot
            // R = [[cos, -sin], [sin, cos]]. Inversa R^T = [[cos, sin], [-sin, cos]]
            double cos_th = std::cos(current_theta);
            double sin_th = std::sin(current_theta);

            // Proiezione vettoriale
            double cmd_vx = v_world_x * cos_th + v_world_y * sin_th;
            double cmd_vy = -v_world_x * sin_th + v_world_y * cos_th;

            // Saturazione
            if (cmd_vx > 0.6) cmd_vx = 0.6; if (cmd_vx < -0.6) cmd_vx = -0.6;
            if (cmd_vy > 0.6) cmd_vy = 0.6; if (cmd_vy < -0.6) cmd_vy = -0.6;
            if (cmd_wz > 0.8) cmd_wz = 0.8; if (cmd_wz < -0.8) cmd_wz = -0.8;

            twist_vx = cmd_vx;
            twist_vy = cmd_vy;
            twist_wz = cmd_wz;
        }
    }

    geometry_msgs::msg::dds_::Twist_ twist_msg;
    twist_msg.linear().x(twist_vx);
    twist_msg.linear().y(twist_vy); // Vy fondamentale per movimento laterale
    twist_msg.angular().z(twist_wz);
    twist_pub.publish(&twist_msg);

    // Chiamata esplicita callback per aggiornare odometria in questo thread
    odometryCallback(this);
}

void VelocityController::readKeyboard(int key) {

    // Tasti Manuali
    if(key==8){
        std::cout << " : X +\n";
        twist_vx += 0.1;
    } else if(key==2){
        std::cout << " : X -\n";
        twist_vx -= 0.1;
    } else if(key==4){
        std::cout << " : Z +\n";
        twist_wz += 0.1;
    } else if(key==6){
        std::cout << " : Z -\n";
        twist_wz -= 0.1;
    } else if(key==0){
        std::cout << " : STOP\n";
        twist_vx = 0.0;
        twist_vy = 0.0;
        twist_wz = 0.0;
        manual_drive = true;
        goto_mode = false;
    } else if(key==7){
        std::cout << " : GOTO GENERIC\n";
        // Reset generico
    } else if(key==3){
        std::cout << "\n>>> START: Target (11, 0) con rotazione +90 gradi <<<\n";
        
        // Salvataggio stato iniziale per interpolazione
        start_x_s = current_x;
        start_y_s = current_y;
        start_th_s = current_theta;

        // Impostazione Target Fisso
        target_x = 11.0;
        target_y = 0.0;
        target_theta = normalizeAngle(start_th_s + (M_PI / 2.0)); 

        manual_drive = false;
        goto_mode = true; 

        std::cout << "Start Pose: (" << start_x_s << ", " << start_y_s << ")\n";
    }
}

void VelocityController::init() { std::cout << "Init. Premi '3' per avvio sequenza." << std::endl; }
void VelocityController::reconfigure() {}
void VelocityController::skip() {}
void VelocityController::missed() {}
void VelocityController::quit() {}

void VelocityController::twistConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {}
void VelocityController::roverOdomConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {}

} // namespace components
} // namespace aurora
