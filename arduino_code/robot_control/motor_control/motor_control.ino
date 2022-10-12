/*********************************************************

This code uses an Arduino uno to command one SMD PWM Motor COntroller (TE-294-001).


***********************************************************/
/*right side*/
const int inAPinRight = 4; 
const int inBPinRight = 2;
const int PWMPinRight = 3;

/*left side*/
const int inAPinLeft = 8; 
const int inBPinLeft = 7;
const int PWMPinLeft = 9;

void setup() {

  pinMode(inAPinRight, OUTPUT);
  pinMode(inBPinRight, OUTPUT);
  pinMode(PWMPinRight, OUTPUT);

  pinMode(inAPinLeft, OUTPUT);
  pinMode(inBPinLeft, OUTPUT);
  pinMode(PWMPinLeft, OUTPUT);
}

void loop() {
  int i;
  digitalWrite(inAPinRight, LOW); //stop motors can be both low or high
  digitalWrite(inBPinRight, LOW);
  digitalWrite(inAPinLeft, LOW); //stop motors can be both low or high
  digitalWrite(inBPinLeft, LOW);
  
  delay(500);
  digitalWrite(inAPinRight, HIGH); // move one direction
  digitalWrite(inBPinRight, LOW);
  digitalWrite(inAPinLeft, LOW); // move one direction
  digitalWrite(inBPinLeft, HIGH);
  
  for (i = 0; i < 200; i++){ 
     analogWrite(PWMPinRight, i);
     analogWrite(PWMPinLeft, i);
     delay(10);
  }
  for (i = 199; i >= 0; i--){ 
     analogWrite(PWMPinRight, i);
     analogWrite(PWMPinLeft, i);
     delay(10);
  }
   delay(500);

  digitalWrite(inAPinRight, LOW); // stop motor
  digitalWrite(inBPinRight, LOW);
  digitalWrite(inAPinLeft, LOW); // stop motor
  digitalWrite(inBPinLeft, LOW);
  delay(500);
  
  digitalWrite(inAPinRight, LOW); // move other direction
  digitalWrite(inBPinRight, HIGH);
  digitalWrite(inAPinLeft, HIGH); // move other direction
  digitalWrite(inBPinLeft, LOW);
  
  for (i = 0; i < 200; i++){
     analogWrite(PWMPinRight,i);
     analogWrite(PWMPinLeft,i);
     delay(10);
  }
  for (i = 199; i >= 0; i--){ 
     analogWrite(PWMPinRight, i);
     analogWrite(PWMPinLeft, i);
     delay(10);
  }
   delay(500);
   

}
