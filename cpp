#include "VelocityController.hpp"
#include <iostream>
#include <sstream>
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
    if(bytesWaiting == 0)
        return -1;
    return getchar() - 48;
}

VelocityController::VelocityController() : VActivity() {

    registerPublisher(&twist_pub, "TwistPub", "rt/cmd_vel");
    registerSubscriber(&odometrySub, "OdometrySub", "rt/odom");

    twist_vx = 0.0;
    twist_vy = 0.0;
    twist_wz = 0.0;

    manual_drive = true;
    goto_mode = false;

    target_x = 2.0;
    target_y = 0.0;
    target_theta = M_PI/2.0;
}

VelocityController::~VelocityController() {}

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

    SampleInfo m_info;
    nav_msgs::msg::dds_::Odometry_ odo_msg;

    if(activity->odometrySub.takeNextData(&odo_msg, &m_info)) {
        std::cout << "ODOMETRY" << std::endl << "(";
        std::cout << odo_msg.pose().pose().position().x() << ", ";
        std::cout << odo_msg.pose().pose().position().y() << ", ";
        std::cout << odo_msg.pose().pose().orientation().z() << ") - (";
        std::cout << odo_msg.twist().twist().linear().x() << ", ";
        std::cout << odo_msg.twist().twist().linear().y() << ", ";
        std::cout << odo_msg.twist().twist().angular().z() << ")" << std::endl;
    }
}

void VelocityController::init() {
    std::cout << "VelocityController::init()" << std::endl;
    std::cout << "(8) X+  (2) X-  (4) Z+  (6) Z-  (0) STOP  (3) GOTO_ROT" << std::endl;
}

void VelocityController::reconfigure() {}
void VelocityController::skip() {}
void VelocityController::missed() {}
void VelocityController::quit() {}

void VelocityController::task() {
    int key = _kbhit();
    readKeyboard(key);

    geometry_msgs::msg::dds_::Twist_ twist_msg;

    if(!manual_drive && goto_mode) {

        SampleInfo m_info;
        nav_msgs::msg::dds_::Odometry_ odo_msg;

        if(odometrySub.takeNextData(&odo_msg, &m_info)) {

            double x = odo_msg.pose().pose().position().x();
            double y = odo_msg.pose().pose().position().y();
            double yaw = odo_msg.pose().pose().orientation().z();

            double dx = target_x - x;
            double dy = target_y - y;
            double dist = sqrt(dx*dx + dy*dy);

            double vx_world = 0.0;
            double vy_world = 0.0;

            if(dist > 0.05) {
                // Movimento dritto nel mondo
                vx_world = 0.3 * (dx/dist);
                vy_world = 0.3 * (dy/dist);
            }

            // CONVERSIONE MONDO → ROBOT (per evitare l’arco)
            double vx_robot =  cos(yaw)*vx_world + sin(yaw)*vy_world;
            double vy_robot = -sin(yaw)*vx_world + cos(yaw)*vy_world;

            twist_msg.linear().x(vx_robot);
            twist_msg.linear().y(vy_robot);

            double dyaw = target_theta - yaw;

            if(fabs(dyaw) > 0.05)
                twist_msg.angular().z(0.4);
            else {
                twist_msg.angular().z(0.0);
                goto_mode = false;
                manual_drive = true;
            }

            twist_pub.publish(&twist_msg);
            return;
        }
    }

    twist_msg.linear().x(twist_vx);
    twist_msg.linear().y(0.0);
    twist_msg.angular().z(twist_wz);

    twist_pub.publish(&twist_msg);
    odometryCallback(this);
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

    } else if(key==3){
        std::cout << " : GOTO_ROT\n";
        twist_vx = 0.0;
        twist_vy = 0.0;
        twist_wz = 0.0;
        manual_drive = false;
        goto_mode = true;

    } else {
        return;
    }
}

} // namespace components
} // namespace aurora
