#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy

class JoyToTwist():
    def __init__(self):
        self.cmd_pub = rospy.Publisher("cmd_out", Twist, queue_size=10)
        self.cmd_sub = rospy.Subscriber("joystick_in", Joy, self.callback)

    def callback(self, data):
        rospy.logdebug("Recieved data")
        msg = Twist()
        speed = data.axes[1]
        steer = data.axes[3]
        msg.linear.x = speed
        msg.angular.z = steer
        self.cmd_pub.publish(msg)

if __name__ == '__main__':
    rospy.init_node('joy_to_twist', anonymous=True)
    node = JoyToTwist()
    rospy.spin()