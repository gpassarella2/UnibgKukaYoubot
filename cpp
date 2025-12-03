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
 * -------------------------------------------------------------------------------
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * - Neither the name of the University of Bergamo nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License LGPL as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version or the BSD license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License LGPL and the BSD license for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License LGPL and BSD license along with this program.
 *
 ******************************************************************************
 */

#include "VelocityController.hpp"
#include <iostream>
#include <sstream>
#include <cmath> // Necessario per le formule matematiche
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

VelocityController::VelocityController() : VActivity() {
	// register the variant publisher
	registerPublisher(&twist_pub, "TwistPub", "rt/cmd_vel");
	registerSubscriber(&odometrySub, "OdometrySub", "rt/odom");
	// registerPublisher(&planRequestPub, "PlanRequestPub", "trajectory2Drequest", planRequestConnectionCallback);

	twist_vx = 0.0;
	twist_vy = 0.0;
	twist_wz = 0.0;

	manual_drive = true;
	
	// Inizializzazione target
	target_x = 0.0;
	target_y = 0.0;
	target_theta = 0.0;
}

VelocityController::~VelocityController() {
}

void VelocityController::twistConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {
	std::cout << "VelocityController::" << port;
	if(matched)
		std::cout << "  CONNECTED #=" << num_connections << std::endl;
	else
		std::cout << "  DISCONNECTED #=" << num_connections << std::endl;
}


void VelocityController::roverOdomConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {
	std::cout << "VelocityController::" << port;
	if(matched)
		std::cout << "  CONNECTED #=" << num_connections << std::endl;
	else
		std::cout << "  DISCONNECTED #=" << num_connections << std::endl;
}


void VelocityController::odometryCallback(VariantActivity* va) {
	VelocityController* activity = (VelocityController*) va;

// ################ USER DEFINED BEGIN ##################

	// Take data
	SampleInfo m_info;
	// NOTA: Usiamo la variabile membro activity->odo_msg invece di una locale
	// nav_msgs::msg::dds_::Odometry_ odo_msg; 

	if(activity->odometrySub.takeNextData(&activity->odo_msg, &m_info)) {
		std::cout << "ODOMETRY"<<std::endl<<"(";
		std::cout<<std::setprecision(6)<< activity->odo_msg.pose().pose().position().x() << ", ";
		std::cout<<std::setprecision(6)<< activity->odo_msg.pose().pose().position().y() << ", ";
		std::cout<<std::setprecision(6)<< activity->odo_msg.pose().pose().orientation().z() << ") - (";
		std::cout<<std::setprecision(6)<< activity->odo_msg.twist().twist().linear().x() << ", ";
		std::cout<<std::setprecision(6)<< activity->odo_msg.twist().twist().linear().y() << ", ";
		std::cout<<std::setprecision(6)<< activity->odo_msg.twist().twist().angular().z() << ")" << std::endl;
		
	}

// ################ USER DEFINED END ####################
}


void VelocityController::init() {
	std::cout << "VelocityController::init()" << std::endl;
	std::cout << "(8) X+  (2) X-  (4) Z+  (6) Z-  (0) STOP  (3) GO" << std::endl;
}

void VelocityController::reconfigure() {
	std::cout << "VelocityController reconfigure" << std::endl;
}

void VelocityController::task() {
	int key = 0;
	key = _kbhit();
	readKeyboard(key);

	geometry_msgs::msg::dds_::Twist_ twist_msg;

	if (manual_drive) {
		// Logica manuale originale
		twist_msg.linear().x(twist_vx);
		twist_msg.linear().y(0.0);	
		twist_msg.angular().z(twist_wz);
	} 
	else {
		// --- LOGICA AUTOMATICA (Richiesta) ---
		
		// 1. Leggiamo direttamente dall'odometria salvata
		double current_x = odo_msg.pose().pose().position().x();
		double current_y = odo_msg.pose().pose().position().y();
		double current_theta = odo_msg.pose().pose().orientation().z();

		// 2. Calcoliamo la distanza
		double dx = target_x - current_x;
		double dy = target_y - current_y;
		double dist = std::sqrt(dx*dx + dy*dy);

		double desired_angle = 0.0;
		double error_angle = 0.0;

		// 3. Macchina a stati semplice: Avvicinamento -> Allineamento
		if (dist > 0.10) {
			// Se siamo lontani, puntiamo alle coordinate
			desired_angle = std::atan2(dy, dx);
			
			// Velocità proporzionale alla distanza (con limite)
			twist_vx = 0.5 * dist; 
			if(twist_vx > 0.4) twist_vx = 0.4;
		} 
		else {
			// Se siamo arrivati, puntiamo all'angolo finale
			desired_angle = target_theta;
			twist_vx = 0.0; // Fermiamo l'avanzamento
			std::cout << "ARRIVATO - ALLINEAMENTO" << std::endl;
		}

		// 4. Calcolo errore angolare
		error_angle = desired_angle - current_theta;

		// Normalizzazione tra -PI e PI
		while (error_angle > 3.14159) error_angle -= 2 * 3.14159;
		while (error_angle < -3.14159) error_angle += 2 * 3.14159;

		// 5. Imposta velocità angolare
		twist_wz = 1.5 * error_angle; 

		// STOP TOTALE
		if (dist < 0.10 && std::abs(error_angle) < 0.05) {
			twist_wz = 0.0;
		}

		// Assegnazione variabili
		twist_msg.linear().x(twist_vx);
		twist_msg.linear().y(0.0);	
		twist_msg.angular().z(twist_wz);
	}

	twist_pub.publish(&twist_msg);

	odometryCallback(this);
}

void VelocityController::skip() {
	std::cout << "[VelocityController]::skip()" << std::endl;
}
void VelocityController::missed() {
	std::cout << "[VelocityController]::missed()" << std::endl;
}

void VelocityController::quit() {
	std::cout << "VelocityController::quit()" << std::endl;
}


void VelocityController::readKeyboard(int key) {

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
		manual_drive = true; // Torna in manuale
	} else if(key==7){
		std::cout << " : GOTO (Manuale Disattivato)\n";
		twist_vx = 0.0;
		twist_vy = 0.0;
		twist_wz = 0.0;
		manual_drive = false;
	}
	else if(key==3){
		// --- NUOVO TASTO 3 ---
		// Leggiamo posizione attuale da odo_msg
		double curr_x = odo_msg.pose().pose().position().x();
		double curr_y = odo_msg.pose().pose().position().y();
		double curr_th = odo_msg.pose().pose().orientation().z();

		// Impostiamo Target: +2 metri X, -2 metri Y
		target_x = curr_x + 2.0;
		target_y = curr_y - 2.0;
		
		// Impostiamo Angolo: -90 gradi (orario) rispetto ad ora
		target_theta = curr_th - 1.57;

		std::cout << " : GOTO START (Target: " << target_x << ", " << target_y << ")\n";
		
		twist_vx = 0.0;
		twist_wz = 0.0;
		manual_drive = false; // Attiva la logica nel task
	}
	else {
//		std::cout << "(8) X+  (2) X-  (4) Z+  (6) Z-  (0) STOP" << std::endl;
		return;
	}
}

} // namespace components
} // namespace aurora
