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
#ifndef AURORA_INPUT_READER_ACTIVITY_H
#define AURORA_INPUT_READER_ACTIVITY_H

#include <stresa/core/runtime/VActivity.hpp>
#include "stresa/core/msgs/geometry_msgsPubSubTypes.h"
#include "aurora/nav_msgsPubSubTypes.h"

using namespace stresa;

namespace aurora {
namespace components {

class VelocityController : public VActivity {
public:
    VelocityController();
    ~VelocityController();

    static void twistConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections);
    static void roverOdomConnectionCallback(VariantActivity* va, std::string port, bool matched, int num_connections);
    static void odometryCallback(VariantActivity* va);

protected:
    void init();
    void reconfigure();
    void skip();
    void missed();
    void task();
    void quit();

private:
    VPublisher<geometry_msgs::msg::dds_::Twist_PubSubType> twist_pub;
    VSubscriber<nav_msgs::msg::dds_::Odometry_PubSubType> odometrySub;

    double twist_vx, twist_vy, twist_wz;
    bool manual_drive;

    void readKeyboard(int key);

    double target_x, target_y, target_theta;

    bool goto_mode;

};

} // namespace components
} // namespace aurora

#endif
