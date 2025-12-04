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

// Variabili statiche per memorizzare la posa iniziale per l'interpolazione
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

VelocityController::VelocityController() : VActivity() {
    registerPublisher(&twist_pub, "TwistPub", "rt/cmd_vel");
    registerSubscriber(&odometrySub, "OdometrySub", "rt/odom");

    twist_vx = 0.0;
    twist_vy = 0.0;
    twist_wz = 0.0;

    // Stato Iniziale
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
        // 1. Aggiorna posizione X, Y globali
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
    
    double dx = target_x - current_x;
    double dy = target_y - current_y;

    double rho = std::sqrt(dx*dx + dy*dy);

    if (rho < 0.1) {
        twist_vx = 0.0;
        twist_vy = 0.0;
        twist_wz = 0.0;
        goal_reached = true;
        manual_drive = true;
        std::cout << ">>> TARGET RAGGIUNTO! Torno in manuale. <<<" << std::endl;
        return;
    }
    
    // Calcolo distanza totale iniziale
    double total_dx = target_x - start_x_s;
    double total_dy = target_y - start_y_s;
    double total_dist = std::sqrt(total_dx*total_dx + total_dy*total_dy);
    
    // Calcolo progresso (0.0 = inizio, 1.0 = fine)
    double progress = 0.0;
    if (total_dist > 0.001) {
        progress = 1.0 - (rho / total_dist);
    }
    if (progress < 0.0) progress = 0.0;
    if (progress > 1.0) progress = 1.0;

    // Interpolazione Angolo: Ruota progressivamente in base alla % di strada fatta
    double total_rotation = normalizeAngle(target_theta - start_th_s);
    double desired_current_theta = start_th_s + (total_rotation * progress);
    
    double theta_error = normalizeAngle(desired_current_theta - current_theta);

    double k_v = 0.5;   
    double k_w = 1.5; // Guadagno rotazione un po' più alto per seguire bene l'interpolazione

    double cmd_vx = k_v * (dx * std::cos(current_theta) + dy * std::sin(current_theta));
    double cmd_vy = k_v * (-dx * std::sin(current_theta) + dy * std::cos(current_theta));
    double cmd_wz = k_w * theta_error;

    if (cmd_vx > 0.5) cmd_vx = 0.5; // Max 0.5 m/s
    if (cmd_vx < -0.5) cmd_vx = -0.5;

    if (cmd_vy > 0.5) cmd_vy = 0.5;
    if (cmd_vy < -0.5) cmd_vy = -0.5;

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
    } else if(key==7){
        std::cout << " : GOTO\n";
        twist_vx = 0.0;
        twist_vy = 0.0;
        twist_wz = 0.0;
        manual_drive = false;
    } else if(key==3){
        std::cout << "\n>>> GOTO COORDINATA CON ROTAZIONE GRADUALE <<<\n";
        
        // Salviamo lo stato iniziale per calcolare il progresso
        start_x_s = current_x;
        start_y_s = current_y;
        start_th_s = current_theta;

        target_x = -5.0;
        target_y = 11.0;
        
        // Target angolo: Start + 90 gradi (M_PI / 2.0)
        target_theta = normalizeAngle(current_theta + (M_PI / 2.0)); 

        manual_drive = false;
        goal_reached = false;

        std::cout << "Start: (" << start_x_s << ", " << start_y_s << ")\n";
        std::cout << "Target: (" << target_x << ", " << target_y << ")\n";
    }
}

void VelocityController::init() { std::cout << "Init. Premi '3' per movimento combinato." << std::endl; }
void VelocityController::reconfigure() {}
void VelocityController::skip() {}
void VelocityController::missed() {}
void VelocityController::quit() {}

void VelocityController::twistConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {}
void VelocityController::roverOdomConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {}

} // namespace components
} // namespace aurora
