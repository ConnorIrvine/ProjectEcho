#include <Arduino.h>
#include <Servo.h>

int servoPin = 3;
Servo Servo1;

void setup() {
  Servo1.attach(servoPin); 
  Serial.begin(9600);
}

void loop() {
  // Read the signal
  double signal = analogRead(A0);
  double angle = signal / 5.68;

  if(angle >= 180)
  {
    angle = 180;
  }
   Servo1.write(angle);
}