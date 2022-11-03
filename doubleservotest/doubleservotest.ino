#include <Servo.h>

Servo pin5;  // servo in pin5, create servo object to control a servo
Servo pin9;  // servo in pin9

int pos;

void drop(Servo &theServo) {
  theServo.write(0);
}

void grab(Servo &theServo) {  
  theServo.write(180);
}

void grasp(int angle, Servo &theServo) {  // sets the servo angle 0 - 180 (90 in the middle)
  theServo.write(angle);
}

void moveSteps(int degreesToMove, Servo &theServo) {
  int oldPos = theServo.read();                                              
  if (degreesToMove > 0) {
    for (pos = oldPos; pos < (oldPos + degreesToMove); pos += 1){
    theServo.write(pos);
    delay(15);
  }} else {
  for (pos = oldPos; pos > (oldPos + degreesToMove); pos -= 1){
    theServo.write(pos);
    delay(15);  
  }}
}

void setup() {
  Serial.begin(9600);
  pin9.attach(9);    // attaches the servo on pin 9 to the servo object
  pin5.attach(5);
}

// Servo names: pin5 & pin9
void loop() {
  grab(pin9);
  moveSteps(60, pin5);
  delay(1500);
  drop(pin9);
  moveSteps(-15, pin5);
  delay(1500);
  moveSteps(90, pin9);
  drop(pin5);
  delay(1500);
  moveSteps(-45, pin9);
  delay(1500);
  
}
