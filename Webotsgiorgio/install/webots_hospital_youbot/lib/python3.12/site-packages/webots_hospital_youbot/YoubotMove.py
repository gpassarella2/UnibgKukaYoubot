#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from rclpy.qos import QoSProfile
import math
#QUESTO è IL CODICE PER TESTARE SE SI MUOVE E SE IL DRIVER è FATTO IN MANIERA GIUSTA

class YoubotDriverTest(Node):
    def __init__(self):
        super().__init__('YoubotDriverTest')

        qos = QoSProfile(depth=10)
        self.pub_twist = self.create_publisher(Twist, 'rover_twist', qos)
        self.sub_odom = self.create_subscription(Odometry, 'odom', self.odom_callback, qos)

        self.cmd = Twist()
        self.counter = 0

    def odom_callback(self, msg):
        x = msg.pose.pose.position.x
        y = msg.pose.pose.position.y
        theta = msg.pose.pose.orientation.z * 180.0 / math.pi
        print(f"Odometry({x:.2f}, {y:.2f}, {theta:.1f})")
#ho fatto un counter casuale per simulare dei movimenti per vedere se gli arrivano i comandi 
    def move_pattern(self):
        if 0 <= self.counter < 25:
            self.cmd.linear.x = 0.2   
            self.cmd.linear.y = 0.0
            self.cmd.angular.z = 0.0
        elif 25 <= self.counter < 50:
            self.cmd.linear.x = 0.0
            self.cmd.linear.y = 0.2   
            self.cmd.angular.z = 0.0
        elif 50 <= self.counter < 75:
            self.cmd.linear.x = 0.0
            self.cmd.linear.y = -0.2  
            self.cmd.angular.z = 0.0
        elif 75 <= self.counter < 100:
            self.cmd.linear.x = 0.0
            self.cmd.linear.y = 0.0
            self.cmd.angular.z = 0.5  
        else:
            self.cmd = Twist()        # stop

        self.pub_twist.publish(self.cmd)
        self.counter += 1


def main(args=None):
    rclpy.init(args=args)
    node = YoubotDriverTest()
    rate = node.create_rate(5)  # 5 Hz

    while rclpy.ok() and node.counter < 120:
        rclpy.spin_once(node, timeout_sec=0)
        node.move_pattern()
        rate.sleep()

    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

