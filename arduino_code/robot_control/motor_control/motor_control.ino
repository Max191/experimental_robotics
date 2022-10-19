#include <ros.h>

/*********************************************************

This code uses an Arduino uno to command one SMD PWM Motor COntroller (TE-294-001).


***********************************************************/
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

/*right side*/
const int inAPinRight = 4; 
const int inBPinRight = 2;
const int PWMPinRight = 3;

/*left side*/
const int inAPinLeft = 8; 
const int inBPinLeft = 7;
const int PWMPinLeft = 9;

bool left_moving_forward = false;
bool left_moving_backward = false;
bool right_moving_forward = false;
bool right_moving_backward = false;

void wheel_control( const geometry_msgs::Twist& cmd_msg) {
   int right_cmd = (int)(cmd_msg.linear.x);
   int left_cmd = (int)(cmd_msg.angular.z);

   //set wheel directions
   if(!left_moving_forward && left_cmd >= 0.f){
      digitalWrite(inAPinLeft, LOW); // move one direction
      digitalWrite(inBPinLeft, HIGH);
      left_moving_forward = true;
      left_moving_backward = false;
   }
   if(!left_moving_backward && left_cmd < 0.f){
      digitalWrite(inAPinLeft, HIGH); // move other direction
      digitalWrite(inBPinLeft, LOW);
      left_moving_backward = true;
      left_moving_forward = false;
   }
   if(!right_moving_forward && right_cmd >= 0.f){
      digitalWrite(inAPinRight, HIGH); // move one direction
      digitalWrite(inBPinRight, LOW);
      right_moving_forward = true;
      right_moving_backward = false;
   }
   if(!right_moving_backward && right_cmd < 0.f){
      digitalWrite(inAPinRight, LOW); // move other direction
      digitalWrite(inBPinRight, HIGH);
      right_moving_backward = true;
      right_moving_forward = false;
   }
   delay(10);

   analogWrite(PWMPinRight, abs(right_cmd));
   analogWrite(PWMPinLeft, abs(left_cmd));
}

ros::Subscriber<geometry_msgs::Twist> wheel_control_sub("/robot_control/right_left_speed_cmd", wheel_control);
ros::NodeHandle  nh;

void setup() {

   pinMode(inAPinRight, OUTPUT);
   pinMode(inBPinRight, OUTPUT);
   pinMode(PWMPinRight, OUTPUT);

   pinMode(inAPinLeft, OUTPUT);
   pinMode(inBPinLeft, OUTPUT);
   pinMode(PWMPinLeft, OUTPUT);

   nh.initNode();

   nh.subscribe(wheel_control_sub);
}

void loop() {
   nh.spinOnce();
   delay(1);
}
