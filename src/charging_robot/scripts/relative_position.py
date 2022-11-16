#!/usr/bin/env python2
import rospy
import tf.transformations as t
from std_msgs.msg import String
from geometry_msgs.msg import Pose
from ar_track_alvar_msgs.msg import AlvarMarkers
from visualization_msgs.msg import Marker

class ReversePose():
    def __init__(self):
        self.pose_pub = rospy.Publisher("robot_relative_pose", Pose, queue_size=10)
        self.pose_sub = rospy.Subscriber("ar_pose_marker", AlvarMarkers, self.callback)
	self.marker_pub = rospy.Publisher("/visualization_marker_robot", Marker, queue_size = 2)

	self.marker = Marker()

	self.marker.header.frame_id = "/camera_color_optical_frame"
	self.marker.header.stamp = rospy.Time.now()
	# set shape, Arrow: 0; Cube: 1 ; Sphere: 2 ; Cylinder: 3
	self.marker.type = 1
	self.marker.id = 0

	# Set the scale of the marker
	self.marker.scale.x = .1
	self.marker.scale.y = .3
	self.marker.scale.z = .1

	# Set the color
	self.marker.color.r = 0.0
	self.marker.color.g = 1.0
	self.marker.color.b = 0.0
	self.marker.color.a = 1.0


    def callback(self, data):
	print("1")
	if data.markers != []:
		print("0")
		ar = data.markers[0].pose.pose
		trans = [ar.position.x, ar.position.y, ar.position.z]
		rot = [ar.orientation.x, ar.orientation.y, ar.orientation.z, ar.orientation.w]

		transform = t.concatenate_matrices(t.translation_matrix(trans), t.quaternion_matrix(rot))
		inversed_transform = t.inverse_matrix(transform)
		
		#print(inversed_transform)
		
		decomp = t.decompose_matrix(inversed_transform)
		print(decomp[2])
		print(decomp[3])
		
		r_rot = t.quaternion_from_euler(decomp[2][0],decomp[2][1],decomp[2][2],'sxyz')
		r_pos = decomp[3]
		

		quat = (ar.orientation.x, ar.orientation.y, ar.orientation.z, ar.orientation.w)
		euler = t.euler_from_quaternion(quat, axes='sxyz')
		x = euler[0]
		y = euler[1]
		z = euler[2]
		print("%f,%f,%f" % (x,y,z))
		print(trans)
		#self.pose_pub.publish(ar)
		
		# Set the pose of the marker
		self.marker.pose.position.x = decomp[3][0]
		self.marker.pose.position.y = decomp[3][1]
		self.marker.pose.position.z = decomp[3][2]
		self.marker.pose.orientation.x = r_rot[0]
		self.marker.pose.orientation.y = r_rot[1]
		self.marker.pose.orientation.z = r_rot[2]
		self.marker.pose.orientation.w = r_rot[3]

		self.marker_pub.publish(self.marker)


if __name__ == '__main__':
    rospy.init_node('relative_position', anonymous=True)
    node = ReversePose()
    rospy.spin()
