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

/*LEDs*/
const int led_pin_1 = 13;
const int led_pin_2 = 12;
const int led_pin_3 = 6;
const int led_pin_4 = 5;

const int charge_state_pin = 14;

const long led_interval = 1000;
unsigned long charge_start_time = 0;

bool left_moving_forward = false;
bool left_moving_backward = false;
bool right_moving_forward = false;
bool right_moving_backward = false;



bool is_charging = false;
bool charge_pin_status = false;

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

void Charge_Indicator() {

  if(is_charging == true){
    digitalWrite(led_pin_1,HIGH);
    unsigned long current_time = millis();
    unsigned long charge_time = current_time - charge_start_time;
    if(charge_time > led_interval){
      digitalWrite(led_pin_2, HIGH);
    }
    if(charge_time > led_interval*2){
      digitalWrite(led_pin_3, HIGH);
    }
    if(charge_time > led_interval*3){
      digitalWrite(led_pin_4, HIGH);
    }
  }
  else{
    digitalWrite(led_pin_1,LOW);
    digitalWrite(led_pin_2,LOW);
    digitalWrite(led_pin_3,LOW);
    digitalWrite(led_pin_4,LOW);
  }

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

   pinMode(led_pin_1, OUTPUT);
   pinMode(led_pin_2, OUTPUT);
   pinMode(led_pin_3, OUTPUT);
   pinMode(led_pin_4, OUTPUT);

   pinMode(charge_state_pin, INPUT);

   nh.initNode();

   nh.subscribe(wheel_control_sub);
}

void loop() {


  charge_pin_status = digitalRead(charge_state_pin);
  if (charge_pin_status == true && is_charging == false){
    is_charging = true;
    charge_start_time = millis();
    Charge_Indicator();
  }
  else if(charge_pin_status == true && is_charging == true){
    Charge_Indicator();
  }
  else if(charge_pin_status == false && is_charging == true){
    is_charging = false;
    Charge_Indicator();      
  }

   nh.spinOnce();
   delay(1);
}
