/*********************************************************

This code uses an Arduino uno to command one SMD PWM Motor COntroller (TE-294-001).


***********************************************************/

const int inAPin = 2;
const int inBPin = 4;
const int PWMPin = 3;

void setup() {

  pinMode(inAPin, OUTPUT);
  pinMode(inBPin, OUTPUT);
  pinMode(PWMPin, OUTPUT);
}

void loop() {
  int i;
  digitalWrite(inAPin, LOW); //stop motors can be both low or high
  digitalWrite(inBPin, LOW);
  
  delay(2000);
  digitalWrite(inAPin, HIGH); // move one direction
  digitalWrite(inBPin, LOW);
  
  for (i = 0; i < 50; i++){ 
     analogWrite(PWMPin, i);
     delay(10);
  }
   delay(2000);

  digitalWrite(inAPin, LOW); // stop motor
  digitalWrite(inBPin, LOW);
  delay(2000);
  
  digitalWrite(inAPin, LOW); // move other direction
  digitalWrite(inBPin, HIGH);
  
  for (i = 0; i < 50; i++){
     analogWrite(PWMPin,i);
     delay(10);
  }
   delay(2000);
   

}
