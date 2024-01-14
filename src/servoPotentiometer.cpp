#include <Arduino.h>
#include <Servo.h>

int servoPin = 3;
Servo Servo1;
int prevAngle = -1;

void setup() {
  Servo1.attach(servoPin); 
  Serial.begin(9600);
}

void loop() {
  // Read the signal
  double signal = analogRead(A0);
  double angle = signal / 5.68;

  /*

  if(button status = 1)
  {
    if(angle < prevAngle)
    {
      // relax the servo motor
      // break the loop before the next code runs
    }

    // in all other cases we just let the next code run
  }

  We want the above code because when contact happens, the user will relax their muscle and the servo will try to go down to a lower angle. Because there is contact,
  the servo motor cannot physically move down to the angle it wants to. As a result, the servo will keep exerting force to go back to 0 degrees. We do not want this to happen
  so when we implement the device there will be a device that will measure when contact is occuring at the metal plate (needs to be not so sensative so every contact triggers the mechanism).
  When there is contact we just have to relax the servo and let the springs do the work keeping the clasp attached to the wheel as intended.
  
  */

 prevAngle = angle;

  if(angle >= 180)
  {
    angle = 180;
  }
   Servo1.write(angle);
}