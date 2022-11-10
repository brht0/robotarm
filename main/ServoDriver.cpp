#include "ServoDriver.h"

#include "Arduino.h"

ServoDriver::ServoDriver(int pin):
    MotorDriver(100, 0.01),
    pin_(pin)
{
}

ServoDriver::~ServoDriver() {
    
}

void ServoDriver::init(){
    servo_.attach(pin_);
}

void ServoDriver::Update(double time){
  double scalar = (time - targetStartTime_) / (targetTime_ - targetStartTime_);

  if(scalar < 0 || scalar > 1){
    return;
  }

  int pos = targetStartAngle_ + scalar * (target_ - targetStartAngle_);
  Serial.println(pos);
  servo_.write(pos);
}

void ServoDriver::ZeroAngle(double position) {
    angle_ = position;
}

void ServoDriver::SetAngle(double angle) {
  angle_ = angle;
}
