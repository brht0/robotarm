// #include "RobotDriver.h"
// #include "Event.hpp"

// ServoDriver servo1(9);
// // ServoDriver servo2(5);

// StepperDriver stepper1(11, 10, 550);
// StepperDriver stepper2(6, 7, 7200);
// StepperDriver stepper3(2, 3, 130);

// int eventIndex = 0;
// Vector<Event> events;

// void setup(){
//     Serial.begin(9600);

//     servo1.init();
//     // servo2.init();
//     stepper1.init();
//     stepper2.init();
//     stepper3.init();

//     double dir = 1.f;

//     Event e0;
//     e0.AddEvent(&servo1, 180.0);
//     e0.AddEvent(&stepper1, dir * -0.0 * 3.14159);
//     e0.AddEvent(&stepper2, dir * 0.0 * 3.14159);
//     e0.AddEvent(&stepper3, dir * 0.0 * 3.14159);

//     events.push_back(e0);

//     delay(500);
//     auto t = GetTimeSeconds();
//     events[0].SetEvents(t, t+3.0);
    
//     //servo1.SetTarget(180, GetTimeSeconds() + 0.1, GetTimeSeconds());
// }

// bool flag1 = true;
// bool flag2 = true;
// bool flag3 = true;

// const unsigned int MAX_MESSAGE_LENGTH = 12;
// #include <stdlib.h>
// double ConvertToDouble(char* message){
//   return atof(message);
// }

// void applyCommand(char* message){
//   double result = ConvertToDouble(message+2);
//   Serial.print("THIs: ");
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

//     //servo1.Update(GetTimeSeconds());
//     auto t = GetTimeSeconds();

//     stepper1.Update(t);
//     stepper2.Update(t);
//     stepper3.Update(t);
//     servo1.Update(t);

//     if(0){
//     if(events[eventIndex].IsDone()){
//       Serial.println("Event done");
//       eventIndex ++;
//       events[eventIndex].SetEvents(t, t + 10.0);
//     }
//     else{
//       if(eventIndex >= events.size()){
//         //Serial.println("Event done");
//       }
//     }
//     }

//     //delay(10);
// }

#include "Timer.hpp"

Timer timer;

void setup(){
  Serial.begin(9600);
  Serial.println(sizeof(int));
  Serial.println(sizeof(unsigned int));
  Serial.println(sizeof(unsigned long));
  Serial.println(sizeof(unsigned long long));
  Serial.println(sizeof(double));
  Serial.println(sizeof(long double));

  timer.Reset();
}

double cumulator = 0;

void loop(){
  cumulator += timer.GetDeltaTimeSeconds();

  Serial.println(cumulator);

  if(cumulator > 1.0){
    Serial.println("Over a second...");
    cumulator -= 1.0;
  }

  timer.Update();
}
