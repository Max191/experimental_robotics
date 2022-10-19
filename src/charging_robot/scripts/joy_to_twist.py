#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy

class RobotControlNode():
    def __init__(self):
        self.cmd_pub = rospy.Publisher("cmd_out", Twist)
        self.cmd_sub = rospy.Subscriber("joystick_in", Twist, self.callback)

    def callback(self, data):
        msg = Twist()
        speed = data.axes[1]
        steer = data.axes[3]
        msg.linear.x = speed
        msg.angluar.z = steer
        self.cmd_pub.publish(msg)

if __name__ == '__main__':
    rospy.init_node('robot_control_node', anonymous=True)
    node = RobotControlNode()
    rospy.spin()