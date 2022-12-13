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

bool IsValidCommand(String command){
  if(command.length() < 3)
    return false;

  if(command[0] == 'B'){
    if(command.length() != 3)
      return false;
    return true;
  }
  else if(command[0] == 'X'){
    if(command.length() < 4)
      return false;

    return true;
  }

  return false;
}


CppInterface io;
Timer timer;

int lastJoystick1 = ' ';

void ApplyCommand(String command){
  if(command.length() && IsValidCommand(command)){
    Serial.println(command);

    if(command[0] == 'B'){
      // lastJoystick1 = command[2];
      if(command[2] == '0'){
        stepper1.SetTarget(stepper1.GetAngle() - 0.1, timer.GetTimeSeconds() + 0.1, timer.GetTimeSeconds());
      }
      if(command[2] == '1'){
        stepper1.SetTarget(stepper1.GetAngle() + 0.1, timer.GetTimeSeconds() + 0.1, timer.GetTimeSeconds());
      }
    }
    else if(command[0] == 'X'){
      lastJoystick1 = command[2];
      if(command[2] == '-'){
        stepper1.SetTarget(stepper1.GetAngle() - 0.01, timer.GetTimeSeconds() + 0.1, timer.GetTimeSeconds());
      }
      else{
        stepper1.SetTarget(stepper1.GetAngle() + 0.01, timer.GetTimeSeconds() + 0.1, timer.GetTimeSeconds());
      }
    }
  }

}

void setup(){
  io.SetupSerial();
  InitMotors();
  timer.Reset();
}

void loop(){
  auto command = io.ReadCommand();
  if(command.length()){
    ApplyCommand(command);
  }
  timer.Update();

  servo1.Update(timer.GetTimeSeconds());
  stepper1.Update(timer.GetTimeSeconds());
  stepper2.Update(timer.GetTimeSeconds());
  stepper3.Update(timer.GetTimeSeconds());

  delay(10);
}
