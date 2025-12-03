/********************************************************************************
 *
 * InputReaderActivity
 *
 * Copyright (c) 2019
 * All rights reserved.
 *
 * Davide Brugali, Università degli Studi di Bergamo
 *
 * -------------------------------------------------------------------------------
 * File: InputReaderActivity.cpp
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

#include "InputReaderActivity.hpp"
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

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    if(bytesWaiting == 0)
        return -1;
    //return bytesWaiting;
    return getchar()-48;
}

InputReaderActivity::InputReaderActivity() : VActivity() {
    // register the variant publisher
    registerPublisher(&twist_pub, "TwistPub", "rt/cmd_vel");
    registerSubscriber(&odometrySub, "OdometrySub", "rt/odom");
    // registerPublisher(&planRequestPub, "PlanRequestPub", "trajectory2Drequest", planRequestConnectionCallback);

    twist_vx = 0.0;
    twist_vy = 0.0;
    twist_wz = 0.0;

    manual_drive = true;

    // Inizializzazione variabili di stato e target
    current_x = 0.0;
    current_y = 0.0;
    current_theta = 0.0;
    
    target_x = 0.0;
    target_y = 0.0;
    auto_mode = false;
}

InputReaderActivity::~InputReaderActivity() {
}

void InputReaderActivity::twistConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {
    std::cout << "InputReaderActivity::" << port;
    if(matched)
        std::cout << "  CONNECTED #=" << num_connections << std::endl;
    else
        std::cout << "  DISCONNECTED #=" << num_connections << std::endl;
}


void InputReaderActivity::roverOdomConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {
    std::cout << "InputReaderActivity::" << port;
    if(matched)
        std::cout << "  CONNECTED #=" << num_connections << std::endl;
    else
        std::cout << "  DISCONNECTED #=" << num_connections << std::endl;
}


void InputReaderActivity::odometryCallback(VariantActivity* va) {
    InputReaderActivity* activity = (InputReaderActivity*) va;

// ################ USER DEFINED BEGIN ##################

    // Take data
    SampleInfo m_info;
    nav_msgs::msg::dds_::Odometry_ odo_msg;

    // PRELIEVO DATI DALL'ODOMETRIA
    if(activity->odometrySub.takeNextData(&odo_msg, &m_info)) {
        
        // AGGIORNAMENTO VARIABILI DI STATO CON I VALORI REALI
        // Questi valori verranno usati nel ciclo di controllo in task()
        activity->current_x = odo_msg.pose().pose().position().x();
        activity->current_y = odo_msg.pose().pose().position().y();
        activity->current_theta = odo_msg.pose().pose().orientation().z();

        std::cout << "ODOMETRY"<<std::endl<<"(";
        std::cout<<std::setprecision(6)<< odo_msg.pose().pose().position().x() << ", ";
        std::cout<<std::setprecision(6)<< odo_msg.pose().pose().position().y() << ", ";
        std::cout<<std::setprecision(6)<< odo_msg.pose().pose().orientation().z() << ") - (";
        std::cout<<std::setprecision(6)<< odo_msg.twist().twist().linear().x() << ", ";
        std::cout<<std::setprecision(6)<< odo_msg.twist().twist().linear().y() << ", ";
        std::cout<<std::setprecision(6)<< odo_msg.twist().twist().angular().z() << ")" << std::endl;
    }

// ################ USER DEFINED END ####################
}


void InputReaderActivity::init() {
    std::cout << "InputReaderActivity::init()" << std::endl;
    std::cout << "(8) X+  (2) X-  (4) Z+  (6) Z-  (0) STOP  (3) TARGET 90 DEG" << std::endl;
}

void InputReaderActivity::reconfigure() {
    std::cout << "InputReaderActivity reconfigure" << std::endl;
}

void InputReaderActivity::task() {
    
    // 1. LETTURA ODOMETRIA (SENSE)
    // Chiamiamo la callback PRIMA di ogni calcolo per avere posizione x, y, theta aggiornate
    odometryCallback(this);

    int key = 0;
    key = _kbhit();
    
    // 2. GESTIONE INPUT UTENTE
    if (key != -1) {
        readKeyboard(key);
    }

    // 3. CALCOLO TRAIETTORIA (PLAN)
    // Usa current_x/y/theta appena aggiornati dall'odometryCallback
    if (auto_mode) {
        
        // Calcolo errore di posizione
        double dx = target_x - current_x;
        double dy = target_y - current_y;
        double dist = std::sqrt(dx*dx + dy*dy);
        
        // Calcolo errore angolare
        double target_angle = std::atan2(dy, dx);
        double angle_err = target_angle - current_theta;

        // Normalizzazione angolo
        while(angle_err > M_PI) angle_err -= 2.0 * M_PI;
        while(angle_err < -M_PI) angle_err += 2.0 * M_PI;

        // Logica di stop
        if (dist < 0.1) {
            std::cout << "TARGET RAGGIUNTO" << std::endl;
            twist_vx = 0.0;
            twist_wz = 0.0;
            auto_mode = false;
            manual_drive = true;
        } else {
            // Unicycle control law
            // Ruota sul posto se l'errore è grande
            if (std::abs(angle_err) > 0.3) {
                twist_vx = 0.0;
                twist_wz = 0.8 * angle_err;
            } else {
                // Avanza e sterza
                twist_vx = 0.4 * dist; 
                if (twist_vx > 0.5) twist_vx = 0.5; // Saturazione
                twist_wz = 1.0 * angle_err;
            }
        }
    }

    // 4. ESECUZIONE (ACT)
    geometry_msgs::msg::dds_::Twist_ twist_msg;
    twist_msg.linear().x(twist_vx);
    twist_msg.linear().y(0.0);  
    twist_msg.angular().z(twist_wz);
    twist_pub.publish(&twist_msg);
}

void InputReaderActivity::skip() {
    std::cout << "[InputReaderActivity]::skip()" << std::endl;
}
void InputReaderActivity::missed() {
    std::cout << "[InputReaderActivity]::missed()" << std::endl;
}

void InputReaderActivity::quit() {
    std::cout << "InputReaderActivity::quit()" << std::endl;
}


void InputReaderActivity::readKeyboard(int key) {

    if(key==8){
        std::cout << " : X +\n";
        twist_vx += 0.1;
        auto_mode = false;
        manual_drive = true;
    } else if(key==2){
        std::cout << " : X -\n";
        twist_vx -= 0.1;
        auto_mode = false;
        manual_drive = true;
    } else if(key==4){
        std::cout << " : Z +\n";
        twist_wz += 0.1;
        auto_mode = false;
        manual_drive = true;
    } else if(key==6){
        std::cout << " : Z -\n";
        twist_wz -= 0.1;
        auto_mode = false;
        manual_drive = true;
    } else if(key==0){
        std::cout << " : STOP\n";
        twist_vx = 0.0;
        twist_vy = 0.0;
        twist_wz = 0.0;
        auto_mode = false;
        manual_drive = true;
    } else if(key==3){
        std::cout << " : CALCOLO TARGET (+90 gradi)\n";
        
        twist_vx = 0.0;
        twist_wz = 0.0;
        
        // Usa le variabili aggiornate dall'odometria per calcolare il target relativo
        double dist = 1.0; 
        target_x = current_x + dist * std::cos(current_theta + M_PI_2);
        target_y = current_y + dist * std::sin(current_theta + M_PI_2);
        
        std::cout << "Target: (" << target_x << ", " << target_y << ")\n";

        manual_drive = false;
        auto_mode = true;
    } else if(key==7){
        std::cout << " : GOTO\n";
        twist_vx = 0.0;
        twist_vy = 0.0;
        twist_wz = 0.0;
        manual_drive = false;
    }
    else {
//      std::cout << "(8) X+  (2) X-  (4) Z+  (6) Z-  (0) STOP" << std::endl;
        return;
    }
}

} // namespace components
} // namespace aurora
