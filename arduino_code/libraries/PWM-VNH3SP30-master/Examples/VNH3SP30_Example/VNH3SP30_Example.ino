#include "VNH3SP30.h"

#define PwmPin 5
#define InAPin 4
#define InBPin 6

VNH3SP30 Motor1(PwmPin, InAPin, InBPin);

int i;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Motor1.Stop();
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  for(i = 0; i++; i <= 255){ Motor1.Move(i, HIGH); delay(50);}
  for(i = 255; i--; i >= 0){ Motor1.Move(i, LOW); delay(50);}
  
  Motor1.Coast();
  delay(5000);
  
}
