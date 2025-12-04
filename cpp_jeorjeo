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
#include <iomanip>
#include <cmath>
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace stresa;

namespace aurora {
namespace components {

// --- Utility per gestione tastiera non bloccante ---
int VelocityController::_kbhit() {
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
    return bytesWaiting;
}

// --- Costruttore ---
VelocityController::VelocityController() : VActivity() {
    // Registrazione interfacce
    registerPublisher(&twist_pub, "TwistPub", "rt/cmd_vel");
    registerSubscriber(&odometrySub, "OdometrySub", "rt/odom");

    // Inizializzazione variabili
    current_x = 0.0;
    current_y = 0.0;
    current_theta = 0.0;
    
    is_moving = false;

    // Tuning dei guadagni (da aggiustare in base al robot reale)
    Kp_linear = 0.5;   
    Kp_angular = 1.0;  
    tolerance_xy = 0.05; // 5 cm di tolleranza
}

VelocityController::~VelocityController() {}

// --- Lifecycle Methods ---

void VelocityController::init() {
    std::cout << "VelocityController Initialized." << std::endl;
    std::cout << "Premi 'G' per inserire coordinate (X Y) target." << std::endl;
    std::cout << "Premi 'S' per Stop immediato." << std::endl;
}

void VelocityController::reconfigure() {}
void VelocityController::skip() {}
void VelocityController::missed() {}
void VelocityController::quit() {
    std::cout << "VelocityController Quit." << std::endl;
}

// --- Odometry Callback ---
// Legge la posizione corrente del robot e aggiorna le variabili membro
void VelocityController::odometryCallback(VariantActivity* va) {
    VelocityController* activity = (VelocityController*) va;
    SampleInfo m_info;
    nav_msgs::msg::dds_::Odometry_ odo_msg;

    if(activity->odometrySub.takeNextData(&odo_msg, &m_info)) {
        activity->current_x = odo_msg.pose().pose().position().x();
        activity->current_y = odo_msg.pose().pose().position().y();
        
        // Conversione semplice per orientamento 2D (assumendo Z axis rotation)
        // Nota: Se usi quaternioni completi, qui servirebbe una conversione Quat->Euler.
        // Assumo che l'odometria dia direttamente Z come yaw o che la struttura sia semplice.
        activity->current_theta = odo_msg.pose().pose().orientation().z(); 
    }
}

// --- Main Task ---
void VelocityController::task() {
    // 1. Aggiorna odometria
    odometryCallback(this);

    // 2. Gestisci Input Utente
    if (_kbhit()) {
        int key = getchar();
        if (key == 'g' || key == 'G') {
            handleUserInput();
        } else if (key == 's' || key == 'S') {
            is_moving = false;
            std::cout << "STOP FORZATO!" << std::endl;
        }
    }

    // 3. Logica di Controllo
    geometry_msgs::msg::dds_::Twist_ twist_msg;
    
    if (is_moving) {
        computeControl(); // Calcola le velocità necessarie

        // Se siamo arrivati (computeControl imposta is_moving a false), fermiamo
        if (!is_moving) {
            twist_msg.linear().x(0.0);
            twist_msg.linear().y(0.0);
            twist_msg.angular().z(0.0);
            std::cout << "Target Raggiunto." << std::endl;
        } else {
            // Calcolo errori per il movimento olo-nomo
            double err_x = target_x - current_x;
            double err_y = target_y - current_y;
            double dist_error = sqrt(err_x*err_x + err_y*err_y);

            // --- LOGICA ROTAZIONE PROPORZIONALE ---
            // Calcoliamo la percentuale di percorso completato (0.0 a 1.0)
            double dist_traveled = initial_distance - dist_error;
            double fraction = dist_traveled / initial_distance;
            if(fraction < 0) fraction = 0;
            if(fraction > 1) fraction = 1;

            // L'angolo target evolve man mano che ci avviciniamo
            // Inizia da start_theta e finisce a start_theta + 90 gradi (PI/2)
            double target_angle_now = start_theta + (M_PI_2 * fraction);
            
            // Calcolo errore angolare
            double err_theta = normalizeAngle(target_angle_now - current_theta);

            // Velocità lineari nel frame GLOBALE (devono essere ruotate nel frame ROBOT)
            double v_x_global = Kp_linear * err_x;
            double v_y_global = Kp_linear * err_y;

            // Conversione da coordinate Globali a Locali del Robot
            // Vx_robot = Vx_glob * cos(th) + Vy_glob * sin(th)
            // Vy_robot = -Vx_glob * sin(th) + Vy_glob * cos(th)
            double c = cos(current_theta);
            double s = sin(current_theta);

            double v_x_robot = v_x_global * c + v_y_global * s;
            double v_y_robot = -v_x_global * s + v_y_global * c;

            // Velocità angolare
            double v_theta = Kp_angular * err_theta;

            // Saturazione di sicurezza (opzionale)
            if(v_x_robot > 0.5) v_x_robot = 0.5;
            if(v_x_robot < -0.5) v_x_robot = -0.5;
            if(v_y_robot > 0.5) v_y_robot = 0.5;
            if(v_y_robot < -0.5) v_y_robot = -0.5;

            twist_msg.linear().x(v_x_robot);
            twist_msg.linear().y(v_y_robot);
            twist_msg.angular().z(v_theta);
            
            // Debug info
            // std::cout << "Dist: " << dist_error << " Frac: " << fraction << " AngErr: " << err_theta << std::endl;
        }
    } else {
        // Se non ci muoviamo, mandiamo zeri
        twist_msg.linear().x(0.0);
        twist_msg.linear().y(0.0);
        twist_msg.angular().z(0.0);
    }

    twist_pub.publish(&twist_msg);
}

// --- Input Handling ---
void VelocityController::handleUserInput() {
    // Arresta momentaneamente il robot mentre si scrive
    geometry_msgs::msg::dds_::Twist_ stop_msg;
    stop_msg.linear().x(0.0); stop_msg.linear().y(0.0); stop_msg.angular().z(0.0);
    twist_pub.publish(&stop_msg);

    std::cout << "\n--- NUOVO TARGET ---" << std::endl;
    std::cout << "Inserisci X target: ";
    std::cin >> target_x;
    std::cout << "Inserisci Y target: ";
    std::cin >> target_y;

    // Salviamo lo stato iniziale per calcolare la proporzione della rotazione
    start_x = current_x;
    start_y = current_y;
    start_theta = current_theta;
    
    double dx = target_x - start_x;
    double dy = target_y - start_y;
    initial_distance = sqrt(dx*dx + dy*dy);

    if (initial_distance < tolerance_xy) {
        std::cout << "Target troppo vicino. Ignorato." << std::endl;
        is_moving = false;
    } else {
        std::cout << "Movimento verso (" << target_x << ", " << target_y << ")" << std::endl;
        std::cout << "Rotazione prevista: +90 gradi durante il tragitto." << std::endl;
        is_moving = true;
    }
    
    // Pulisce il buffer di input (newline residui)
    std::cin.ignore();
}

// --- Control Logic Helper ---
void VelocityController::computeControl() {
    double dx = target_x - current_x;
    double dy = target_y - current_y;
    double distance = sqrt(dx*dx + dy*dy);

    if (distance < tolerance_xy) {
        is_moving = false;
    }
}

// --- Normalize Angle ---
// Assicura che l'angolo sia tra -PI e +PI per evitare rotazioni inutili (es. girare di 350 gradi invece di -10)
double VelocityController::normalizeAngle(double angle) {
    while (angle > M_PI) angle -= 2.0 * M_PI;
    while (angle < -M_PI) angle += 2.0 * M_PI;
    return angle;
}

} // namespace components
} // namespace aurora
