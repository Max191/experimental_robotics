#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist

class RobotControlNode():
    def __init__(self):
        self.speed = 0.0
        self.steer = 0.0
        self.speed_steer_msg = Twist()
        self.speed_steer_msg.linear.x = self.speed
        self.speed_steer_msg.angular.z = self.steer
        self.speed_steer_pub = rospy.Publisher("cmd_out", Twist, queue_size=10)
        self.sub = rospy.Subscriber("joystick_in", Twist, self.callback)

    def callback(self, data):
        speed_scale = float(rospy.get_param("/robot_control/speed_scale"))
        steer_scale = float(rospy.get_param("/robot_control/steer_scale"))
        max_speed = float(rospy.get_param("/robot_control/max_speed"))
        max_steer = float(rospy.get_param("/robot_control/max_steer"))
        self.speed = self.bound((data.linear.x) * speed_scale, -max_speed, max_speed)
        self.steer = self.bound((data.angular.z) * steer_scale, -max_steer, max_steer)
        self.speed_steer_msg.linear.x = self.speed
        self.speed_steer_msg.angular.z = self.steer
    
    def publish_cmd(self):
        self.speed_steer_pub.publish(self.speed_steer_msg)

    def bound(self, val, mn, mx):
        return max(min(mx, val), mn)

if __name__ == '__main__':
    rospy.init_node('robot_control_node', anonymous=True)
    node = RobotControlNode()
    rate = rospy.Rate(20)
    while not rospy.is_shutdown():
        node.publish_cmd()
        rate.sleep()