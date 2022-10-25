#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist
import numpy as np

class SpeedSteerToRL():
    def __init__(self):
        self.wheel_sep = float(rospy.get_param("/speed_steer_to_rl/wheel_separation"))
        self.rl_speed_pub = rospy.Publisher("control_out", Twist, queue_size=10)
        self.sub = rospy.Subscriber("cmd_in", Twist, self.callback)

    def callback(self, data):
        msg = Twist()
        speed_to_signal = float(rospy.get_param("/speed_steer_to_rl/speed_to_signal"))
        max_speed = float(rospy.get_param("/speed_steer_to_rl/max_signal"))/speed_to_signal
        speed = data.linear.x
        steer = np.radians(data.angular.z)
        vel_diff = steer * self.wheel_sep
        right_speed = self.bound(speed, -max_speed, max_speed)
        left_speed = right_speed = self.bound(speed, -max_speed, max_speed)

        right_speed = self.bound(right_speed + vel_diff/2.0, -max_speed, max_speed)
        left_speed = self.bound(left_speed - vel_diff/2.0, -max_speed, max_speed)

        if abs(right_speed) == max_speed:
            left_speed = self.bound(right_speed - vel_diff, -max_speed, max_speed)
        elif abs(left_speed) == max_speed:
            right_speed = self.bound(left_speed + vel_diff, -max_speed, max_speed)

        msg.linear.x = right_speed * speed_to_signal
        msg.angular.z = left_speed * speed_to_signal
        self.rl_speed_pub.publish(msg)

    def bound(self, val, mn, mx):
        return max(min(mx, val), mn)

if __name__ == '__main__':
    rospy.init_node('robot_control_node', anonymous=True)
    SpeedSteerToRL()
    rospy.spin()