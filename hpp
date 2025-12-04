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
 * File: VelocityController.hpp
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
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of the University of Bergamo nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
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
 ******************************************************************************/
#ifndef VELOCITYCONTROLLER_HPP_
#define VELOCITYCONTROLLER_HPP_

#include <stresa/core/VActivity.hpp>
#include <stresa/core/Variant.hpp>
#include <string>
#include <vector>

// Messaggi DDS (adattare in base alle definizioni esatte nel tuo progetto)
#include <geometry_msgs/msg/dds_/Twist_.h>
#include <nav_msgs/msg/dds_/Odometry_.h>

using namespace stresa;

namespace aurora {
namespace components {

class VelocityController : public VActivity {
public:
    VelocityController();
    virtual ~VelocityController();

    // Metodi del ciclo di vita del componente
    void init();
    void reconfigure();
    void task();
    void skip();
    void missed();
    void quit();
    void twistConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections);
    void odometryConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections);    
    static void odometryCallback(VariantActivity* va);

protected:
    // Publisher per inviare comandi di velocità
    VariantPublisher twist_pub;
    // Subscriber per leggere la posizione corrente
    VariantSubscriber odometrySub;

private:
    // Funzioni interne
    int _kbhit();                 // Per controllare se un tasto è premuto
    void handleUserInput();       // Gestisce l'input da tastiera
    void computeControl();        // Calcola le velocità
    double normalizeAngle(double angle); // Normalizza l'angolo tra -PI e +PI

    // Stato del robot
    double current_x, current_y, current_theta;
    
    // Stato del target
    double target_x, target_y;
    double start_x, start_y, start_theta; // Per calcolare la proporzione
    double initial_distance;              // Distanza totale all'inizio del movimento
    bool is_moving;

    // Parametri del controllore (Guadagni)
    double Kp_linear;  // Guadagno proporzionale per X e Y
    double Kp_angular; // Guadagno proporzionale per l'orientamento
    double tolerance_xy; // Tolleranza di arrivo (metri)
};

} // namespace components
} // namespace aurora

#endif /* VELOCITYCONTROLLER_HPP_ */
