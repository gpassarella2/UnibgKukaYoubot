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

    double desired_heading = std::atan2(dy, dx);
    double alpha = normalizeAngle(desired_heading - current_theta);

    double beta = normalizeAngle(target_theta - desired_heading);

    if (rho < 0.05) {
        twist_vx = 0.0;
        twist_wz = 0.0;
        goal_reached = true;
        manual_drive = true;
        std::cout << ">>> TARGET RAGGIUNTO! Torno in manuale. <<<" << std::endl;
        return;
    }
    
    double k_rho = 0.5;   
    double k_alpha = 1.2; 
    double k_beta = -0.3; 

    if (std::abs(alpha) > M_PI / 2.0) {
        twist_vx = 0.0; 
        twist_wz = 0.6 * (alpha > 0 ? 1 : -1); 
    } else {
        twist_vx = k_rho * rho;
        twist_wz = k_alpha * alpha + k_beta * beta;
    }

    if (twist_vx > 0.5) twist_vx = 0.5; // Max 0.5 m/s
    if (twist_wz > 1.0) twist_wz = 1.0; // Max 1.0 rad/s
    if (twist_wz < -1.0) twist_wz = -1.0;
    
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
    twist_msg.linear().y(0.0);    
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
	} else if(key==7){
		std::cout << " : GOTO\n";
		twist_vx = 0.0;
		twist_vy = 0.0;
		twist_wz = 0.0;
		manual_drive = false;
	} else if(key==3){
                std::cout << "\GOTO TRASL\n";
                
                double local_x = 2.0; 
                double local_y = 2.0; 
                double local_theta = M_PI / 2.0; 

                double cos_th = cos(current_theta);
                double sin_th = sin(current_theta);

                target_x = current_x + (local_x * cos_th - local_y * sin_th);
                target_y = current_y + (local_x * sin_th + local_y * cos_th);
                
                target_theta = normalizeAngle(current_theta + local_theta);

                manual_drive = false;
                goal_reached = false;

                std::cout << "Start Pose: (" << current_x << ", " << current_y << ")\n";
                std::cout << "Global Target: (" << target_x << ", " << target_y << ")\n";
                std::cout << "Il robot calcolera' la curva in tempo reale...\n";
            }
}

void VelocityController::init() { std::cout << "Init. Premi '3' per arco automatico." << std::endl; }
void VelocityController::reconfigure() {}
void VelocityController::skip() {}
void VelocityController::missed() {}
void VelocityController::quit() {}

void VelocityController::twistConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {}
void VelocityController::roverOdomConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {}

} // namespace components
} // namespace aurora
