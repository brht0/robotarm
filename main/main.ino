#include "ServoDriver.h"
#include "StepperDriver.h"
#include "CppInterface.hpp"
#include "Utils.hpp"

bool superSlowMode = true;
bool halt = false;

CppInterface cppInterface;
Timer motorTimer;

ServoDriver servo1(motorTimer, 9);
StepperDriver stepper1(motorTimer, 11, 10, 550, 50);  // elbow
StepperDriver stepper2(motorTimer, 6, 7, 7200, 600);   // shoulder
StepperDriver stepper3(motorTimer, 2, 3, 130, 50);    // base

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
  Joystick,
  Halt,
  Continue
};

CommandType GetCommandType(const String& command){
  if(command.length() < 3){
    return CommandType::None;
  }

  if(command[0] == 'H'){
    return CommandType::Halt;
  }

  if(command[0] == 'C'){
    return CommandType::Continue;
  }

  if(command[0] == 'B'){
    return CommandType::Button;
  }

  if(command[0] == 'X' || command[0] == 'Y' || command[0] == 'R'){
    return CommandType::Joystick;
  }

  return CommandType::None;
}

Joystick GetJoystickType(const String& command){
  char first = command[0];
  if(first == 'X') return Joystick::X;
  if(first == 'Y') return Joystick::Y;
  if(first == 'R') return Joystick::R;
  return Joystick::None;
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
      else if(parameter == 12)
        superSlowMode = !superSlowMode;
      break;
    }
    case CommandType::Halt:{
      halt = true;
      break;
    }
    case CommandType::Continue:{
      halt = false;
      break;
    }
  }
}

void UpdateMotorTargets(){
  double x = joystickValues[(int)Joystick::X];
  double y = joystickValues[(int)Joystick::Y];
  double r = joystickValues[(int)Joystick::R];

  double k_x = 20.0;
  double k_y = 20.0;
  double k_r = -300.0;

  if(superSlowMode){
    k_x *= 0.33;
    k_y *= 0.1;
    k_r *= 0.1;
  }

  if(halt){
    k_x *= 0.0;
    k_y *= 0.0;
    k_r *= 0.0;
  }

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

  if(updateTimer.GetTimeSeconds() > 0.05){
    UpdateMotorTargets();
    updateTimer.Reset();
  }

  servo1.Update();
  stepper1.Update();
  stepper2.Update();
  stepper3.Update();
}
