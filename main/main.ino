#include "ServoDriver.h"
#include "StepperDriver.h"
#include "IO.hpp"

#include <stdlib.h>

double ConvertToDouble(char* message){
  return atof(message);
}
double ConvertToDouble(String message){
  return atof(message.c_str());
}

ServoDriver servo1(9);
StepperDriver stepper1(11, 10, 550); // kyynerpää
StepperDriver stepper2(6, 7, 7200); // olkapää
StepperDriver stepper3(2, 3, 130); // alusta

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
  else if(command[0] == 'X' || command[0] == 'Y' || command[0] == 'R'){
    if(command.length() < 3)
      return false;

    return true;
  }

  return false;
}


CppInterface io;
Timer timer;
Timer updateTimer;

String lastJoystickX = "0";
String lastJoystickY = "0";
String lastJoystickR = "0";

void ApplyCommand(String command){
  if(command.length() >= 3){
    //Serial.println(command);

    if(command[0] == 'B'){
      // lastJoystick1 = command[2];
      if(command[2] == '0'){
        stepper1.SetTarget(stepper1.GetAngle() - 5, timer.GetTimeSeconds() + 0.1, timer.GetTimeSeconds());
      }
      if(command[2] == '1'){
        stepper1.SetTarget(stepper1.GetAngle() + 5, timer.GetTimeSeconds() + 0.1, timer.GetTimeSeconds());
      }
      if(command[2] == '5'){
        servo1.SetTarget(0.0, timer.GetTimeSeconds() + 0.1, timer.GetTimeSeconds());
      }
      if(command[2] == '4'){
        servo1.SetTarget(180.0, timer.GetTimeSeconds() + 0.1, timer.GetTimeSeconds());
      }
    }
    else if(command[0] == 'X'){
      lastJoystickX = command.substring(2);
    }
    else if(command[0] == 'Y'){
      lastJoystickY = command.substring(2);
    }
    else if(command[0] == 'R'){
      lastJoystickR = command.substring(2);
    }
  }

}

void UpdateMotorTargets(){
  double x = ConvertToDouble(lastJoystickX);
  double y = ConvertToDouble(lastJoystickY);
  double r = ConvertToDouble(lastJoystickR);

  double k_x = 0.0001;
  double k_y = 0.0001;
  double k_z = 0.0001;

  if(0){
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.print(r);
  Serial.print("\n");}

  // stepper3.SetTarget(stepper3.GetAngle(), timer.GetTimeSeconds() + 0.5,  
  // stepper3.SetTarget(stepper3.GetAngle(), timer.GetTimeSeconds() + 0.5,  
  // stepper3.SetTarget(stepper3.GetAngle(), timer.GetTimeSeconds() + 0.5,  
}

void setup(){
  io.SetupSerial();
  InitMotors();
  timer.Reset();
  updateTimer.Reset();
}


void loop(){
  timer.Update();
  auto command = io.ReadCommand();
  if(command.length()){
    ApplyCommand(command);
  }

  updateTimer.Update();
  if(updateTimer.GetTimeSeconds() > 0.05){
    UpdateMotorTargets();
    updateTimer.Reset();
  }

  servo1.Update(timer.GetTimeSeconds());
  stepper1.Update(timer.GetTimeSeconds());
  stepper2.Update(timer.GetTimeSeconds());
  stepper3.Update(timer.GetTimeSeconds());

  //delay(10);
}
