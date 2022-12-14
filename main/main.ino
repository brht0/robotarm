#include "ServoDriver.h"
#include "StepperDriver.h"
#include "CppInterface.hpp"
#include "Utils.hpp"

CppInterface cppInterface;
Timer motorTimer;

ServoDriver servo1(motorTimer, 9);
StepperDriver stepper1(motorTimer, 11, 10, 550);  // elbow
StepperDriver stepper2(motorTimer, 6, 7, 7200);   // shoulder
StepperDriver stepper3(motorTimer, 2, 3, 130);    // base

enum class Button{
  R1 = 0,
  L1,
  X,
  NoButton
};

enum class Joystick{
  X = 0,
  Y,
  R,
  None
};

long double joystickValues[3] = {0.0, 0.0, 0.0};

enum class CommandType{
  None = 0,
  Button,
  Joystick
};

CommandType GetCommandType(const String& command){
  if(command.length() < 3){
    return CommandType::None;
  }

  if(command[0] == 'B'){
    return CommandType::Button;
  }

  if(command[0] == 'X' || command[0] == 'Y' || command[0] == 'R'){
    return CommandType::Joystick;
  }
}

Joystick GetJoystickType(const String& command){
  char first = command[0];
  if(first == 'X') return Joystick::X;
  if(first == 'Y') return Joystick::Y;
  if(first == 'R') return Joystick::R;
}

Timer timer;
Timer updateTimer;

void ApplyCommand(String command){
  if(command.length() < 3)
    return;

  auto commandType = GetCommandType(command);
  switch(GetCommandType(command)){
    case CommandType::Joystick:{
      double parameter = ConvertToDouble(command.substring(2));
      auto joystick = GetJoystickType(command);
      joystickValues[(int)joystick] = parameter;
      break;
    }
    case CommandType::Button:{
      int parameter = ConvertToInt(command.substring(2));
      if(parameter == 4) servo1.SetVelocity(1000.0);
      else if(parameter == 5) servo1.SetVelocity(-1000.0);
      break;
    }
  }
}

void UpdateMotorTargets(){
  double x = joystickValues[(int)Joystick::X];
  double y = joystickValues[(int)Joystick::Y];
  double r = joystickValues[(int)Joystick::R];

  double k_x = 1.0;
  double k_y = 1.0;
  double k_r = 1.0;

  if(0){
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.print(r);
  Serial.print("\n");}

  stepper3.SetVelocity(k_x * x);
  stepper2.SetVelocity(k_y * y);
  stepper1.SetVelocity(k_r * r);
}

void setup(){
  cppInterface.SetupSerial();
  timer.Reset();
  updateTimer.Reset();
}


void loop(){
  motorTimer.Update();
  updateTimer.Update();

  auto command = cppInterface.ReadCommand();
  if(command.length()){
    ApplyCommand(command);
  }

  if(updateTimer.GetTimeSeconds() > 0.5){
    UpdateMotorTargets();
    updateTimer.Reset();
    Serial.println(String((long)stepper1.GetPosition()));
  }

  servo1.Update();
  stepper1.Update();
  stepper2.Update();
  stepper3.Update();
}
