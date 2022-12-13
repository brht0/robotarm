#include "ServoDriver.h"
#include "StepperDriver.h"
#include "IO.hpp"

#include <stdlib.h>

double ConvertToDouble(char* message){
  return atof(message);
}

ServoDriver servo1(9);
StepperDriver stepper1(11, 10, 550);
StepperDriver stepper2(6, 7, 7200);
StepperDriver stepper3(2, 3, 130);

void InitMotors(){
  servo1.init();
  stepper1.init();
  stepper2.init();
  stepper3.init();
}

// void applyCommand(char* message){
//   double result = ConvertToDouble(message+2);
//   Serial.print("This: ");
//   Serial.print(result);
//   Serial.print("\n");

//   if(message[0] == 'z' && message[1] == 'e' && message[2] == 'r' && message[3] == 'o'){
//     // todo
//     stepper1.SetAngle(0);
//     stepper2.SetAngle(0);
//     stepper3.SetAngle(0);
//     stepper1.SetTarget(0, 0, 1);
//     stepper2.SetTarget(0, 0, 1);
//     stepper3.SetTarget(0, 0, 1);
//   }

//   if(message[0] == 's'){
//     result = message[2] == 'a' ? 0.0 : 180.0;
//     if(message[2] == 'a'|| message[2] == 'k'){
//       servo1.SetTarget(result, GetTimeSeconds() + 1.0, GetTimeSeconds());
//     }
//   }
//   if(message[0] == '2'){
//     stepper1.SetTarget(result*(3.14159/180.0), GetTimeSeconds() + 1.0, GetTimeSeconds());
//   }
//   if(message[0] == '1'){
//     stepper2.SetTarget(result*(3.14159/180.0), GetTimeSeconds() + 1.0, GetTimeSeconds());
//   }
//   if(message[0] == '0'){
//     stepper3.SetTarget(result*(3.14159/180.0), GetTimeSeconds() + 1.0, GetTimeSeconds());
//   }
// }

// void loop(){
//     //Check to see if anything is available in the serial receive buffer
//     while (Serial.available() > 0)
//     {
//       //Create a place to hold the incoming message
//       static char message[MAX_MESSAGE_LENGTH];
//       static unsigned int message_pos = 0;

//       //Read the next available byte in the serial receive buffer
//       char inByte = Serial.read();

//       //Message coming in (check not terminating character) and guard for over message size
//       if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
//       {
//         //Add the incoming byte to our message
//         message[message_pos] = inByte;
//         message_pos++;
//       }
//       //Full message received...
//       else
//       {
//         //Add null character to string
//         message[message_pos] = '\0';

//         //Print the message (or do other things)
//         applyCommand(message);

//         //Reset for the next message
//         message_pos = 0;
//       }
//     }

//     auto t = GetTimeSeconds();

//     stepper1.Update(t);
//     stepper2.Update(t);
//     stepper3.Update(t);
//     servo1.Update(t);


//     //delay(10);
// }

CppInterface io;

void setup(){
  io.SetupSerial();
  //InitMotors();
}

void loop(){
  //Serial.println("Checking for commands: ");
  auto vec = io.ReadCommand();
  for(auto x : vec){
    Serial.println(x);
  }
  delay(10);

  // cumulator += timer.GetDeltaTimeSeconds();

  // if(cumulator > 2.0){
  //   Serial.println("Pushing to vector: " + String(vec.size()));
  //   vec.push_back(counter ++);
  //   for(auto& i : vec){
  //     Serial.println(i);
  //   }
  //   cumulator -= 1.0;
  // }
  // timer.Update();
}
