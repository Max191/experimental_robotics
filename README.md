# experimental_robotics
Run the following commands:

catkin_make

source devel/setup.bash

Notes

	- http://wiki.ros.org/melodic/Installation/Ubuntu
	- git clone https://github.com/Max191/experimental_robotics
	- source ./devel/setup.sh
	- catkin_make
	- sudo apt-get install ros-melodic-rosserial-arduino
	- sudo apt-get install ros-melodic-rosserial
	- sudo apt-get install ros-melodic-joy
	- #!/usr/bin/env python3 - > #!/usr/bin/env python2 in script files
	- https://github.com/IntelRealSense/librealsense/blob/master/doc/distribution_linux.md
	- secure boot password - "password" - entered during sudo apt-get install librealsense2-dkms command
	- disable secure boot - enroll MOK key0 - enter secure boot password - reboot - camera works
	- sudo apt-get install ros-melodic-realsense2-camera
	- sudo apt-get install ros-melodic-realsense2-description
	- sudo apt-get install ros-melodic-ar-track-alvar
	- sudo apt-get install ros-melodic-find-object-2d
	- roslaunch realsense2_camera rs_camera.launch
	- rosrun find_object_2d find_object_2d image:=/camera/color/image_raw
	- Add object for find_object_2d to look for
	- roslaunch charging_robot usb_cam_ar_track.launch
	- rosrun charging_robot relative_position.py

