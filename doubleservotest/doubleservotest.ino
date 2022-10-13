#include <Servo.h>

Servo myservo5;  // (pin5) create servo object to control a servo
Servo myservo9;  // (pin9)

void drop5() {       // servo position 0 (min)
  myservo5.write(0);
}
void drop9() {       
  myservo9.write(0);
}

void grab5() {         // servo position 180 (max)
  myservo5.write(180);
}
void grab9() {         
  myservo9.write(180);
}

void grasp5(int angle) {  // sets the servo angle 0 - 180 (90 in the middle)
  myservo5.write(angle);
}
void grasp9(int angle) {  
  myservo9.write(angle);
}

int pos9 = myservo9.read();

//toimii ekan kerran, ei liikuta toisella
void moveSteps5(int degreesToMove) {
  int pos5 = myservo5.read();                                              //int oldPos5 = pos5;
  pos5 = 0;
  for (pos5; pos5 <= degreesToMove; pos5 += 1){                            //for (oldPos5 = pos5; oldPos5 <= (oldPos5 + degreesToMove); pos5 += 1){
    myservo5.write(pos5);
    delay(15);
  }
}

void setup() {
  Serial.begin(9600);
  myservo9.attach(9);    // attaches the servo on pin 9 to the servo object
  myservo5.attach(5);
}

void loop() {
  moveSteps5(90);
  delay(10000);
  moveSteps5(90);
  delay(5000);
  drop5();
  delay(10000);



  //grasp5(1 + myservo5.read());
  //grasp9(1 + myservo9.read());
  //delay(1000);
  //drop5();
  //drop9();
  //delay(1000);
  
  //Serial.println(myservo.read()); // returns the angle 
}
