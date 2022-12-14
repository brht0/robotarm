#include "ServoDriver.h"

#include "Arduino.h"

ServoDriver::ServoDriver(const Timer& timer, int pin):
  MotorDriver(timer),
  pin_(pin),
  pinAttached(false)
{
}

ServoDriver::~ServoDriver() {
}

void ServoDriver::Update(){
  if(!pinAttached){
    AttachPin();
    pinAttached = true;
  }

  position_ += ((long double)angleVelocity_ / (long double)(2.0 * 3.14159));

  if(position_ > maxPosition_) position_ = maxPosition_;
  if(position_ < minPosition_) position_ = minPosition_;

  servo_.write(position_);
}

void ServoDriver::AttachPin() {
  servo_.attach(pin_);
}
