#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist

class PanTiltNode():
    def __init__(self):
        self.tilt = 90
        self.pan = 90
        self.pub = rospy.Publisher("pan_tilt_controller/cmd_vel", Twist)
        init_msg = Twist()
        init_msg.linear.x = 90
        init_msg.angular.z = 90
        self.pub.publish(init_msg)
        self.control_scale = 0.5
        self.sub = rospy.Subscriber("cmd_vel", Twist, self.callback)

    def callback(self, data):
        tilt_joy = data.linear.x - 0.5
        pan_joy = data.angular.z - 0.5
        self.tilt = self.bound(self.tilt + tilt_joy * self.control_scale, 0, 180)
        self.pan = self.bound(self.pan + pan_joy * self.control_scale, 0, 180)

        msg = Twist()
        msg.linear.x = self.tilt
        msg.angular.z = self.pan
        self.pub.publish(msg)

    def bound(self, val, mn, mx):
        return max(min(mx, val), mn)

if __name__ == '__main__':
    rospy.init_node('pan_tilt_controller', anonymous=True)
    PanTiltNode()
    rospy.spin()