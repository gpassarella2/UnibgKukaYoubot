/********************************************************************************
 * VelocityController.cpp
 ********************************************************************************/

#include "VelocityController.hpp"
#include <iostream>
#include <sstream>
#include <cmath> 
#include <algorithm>
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
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }
    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    if(bytesWaiting == 0) return -1;
    return getchar()-48;
}

VelocityController::VelocityController() : VActivity() {
	registerPublisher(&twist_pub, "TwistPub", "rt/cmd_vel");
	registerSubscriber(&odometrySub, "OdometrySub", "rt/odom");

	twist_vx = 0.0;
	twist_vy = 0.0;
	twist_wz = 0.0;
	manual_drive = true;
	
	target_x = 0.0; 
	target_y = 0.0; 
	target_theta = 0.0;
}

VelocityController::~VelocityController() {
}

void VelocityController::twistConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {
	std::cout << "TwistPub" << (matched ? " CONNECTED" : " DISCONNECTED") << std::endl;
}

void VelocityController::roverOdomConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections) {
	std::cout << "OdometrySub" << (matched ? " CONNECTED" : " DISCONNECTED") << std::endl;
}

void VelocityController::odometryCallback(VariantActivity* va) {
	VelocityController* activity = (VelocityController*) va;
	SampleInfo m_info;
	
	// --- MODIFICA: Aggiorniamo direttamente la variabile membro della classe ---
	// Non creiamo una variabile locale 'odo_msg', usiamo activity->odo_msg
	if(activity->odometrySub.takeNextData(&activity->odo_msg, &m_info)) {
		// Dati aggiornati in activity->odo_msg
	}
}

void VelocityController::init() {
	std::cout << "VelocityController::init()" << std::endl;
	std::cout << "(8) X+  (2) X-  (4) Z+  (6) Z-  (0) STOP  (3) GO" << std::endl;
}

void VelocityController::reconfigure() {
}

void VelocityController::task() {
	int key = _kbhit();
	readKeyboard(key);

	geometry_msgs::msg::dds_::Twist_ twist_msg;

	if (!manual_drive) {
		// --- USIAMO DIRETTAMENTE I COMANDI DELL'ODOMETRIA ---
		
		// Accesso diretto alla struttura dati
		double x_robot = odo_msg.pose().pose().position().x();
		double y_robot = odo_msg.pose().pose().position().y();
		double theta_robot = odo_msg.pose().pose().orientation().z();

		// 1. Calcola differenze
		double dx = target_x - x_robot;
		double dy = target_y - y_robot;
		double dist = std::sqrt(dx*dx + dy*dy);

		double desired_angle = 0.0;
		double error_angle = 0.0;

		// SE SIAMO LONTANI (> 10 cm)
		if (dist > 0.10) {
			// Punta verso le coordinate
			desired_angle = std::atan2(dy, dx);
			
			// Velocità proporzionale alla distanza
			twist_vx = 0.5 * dist; 
			if(twist_vx > 0.4) twist_vx = 0.4;
		} 
		// SE SIAMO ARRIVATI
		else {
			// Punta all'angolo finale
			desired_angle = target_theta;
			twist_vx = 0.0; 
			std::cout << "ARRIVATO - ALLINEAMENTO" << std::endl;
		}

		// 2. Calcolo errore angolo
		error_angle = desired_angle - theta_robot;

		// Normalizzazione angolo
		while (error_angle > 3.14159) error_angle -= 2 * 3.14159;
		while (error_angle < -3.14159) error_angle += 2 * 3.14159;

		// Rotazione
		twist_wz = 1.5 * error_angle;

		// Stop totale se finito
		if (dist < 0.10 && std::abs(error_angle) < 0.05) {
			twist_wz = 0.0;
		}
	}

	twist_msg.linear().x(twist_vx);
	twist_msg.linear().y(0.0);    
	twist_msg.angular().z(twist_wz);
	
	twist_pub.publish(&twist_msg);
	odometryCallback(this);
}

void VelocityController::skip() {}
void VelocityController::missed() {}
void VelocityController::quit() {}

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
		twist_vx = 0.0; twist_wz = 0.0;
		manual_drive = true;
	} else if(key==3){
		// Imposta Target usando i valori correnti dall'odometria per calcolare il relativo
		double start_x = odo_msg.pose().pose().position().x();
		double start_y = odo_msg.pose().pose().position().y();
		double start_theta = odo_msg.pose().pose().orientation().z();

		target_x = start_x + 2.0; 
		target_y = start_y - 2.0; 
		target_theta = start_theta - 1.57; 

		std::cout << " : GOTO START (Target: " << target_x << ", " << target_y << ")\n";
		manual_drive = false; 
	} 
}

} // namespace components
} // namespace aurora
