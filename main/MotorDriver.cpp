#include "MotorDriver.h"

MotorDriver::MotorDriver(double maxSpeed, double angleEpsilon):
    maxSpeed_(maxSpeed), angleEpsilon_(angleEpsilon)
{
}

MotorDriver::~MotorDriver() {
}

double MotorDriver::GetAngle() {
    return angle_;
}

#include "Arduino.h"

void MotorDriver::SetTarget(double angle, double targetTime, double time) {
    target_ = angle;
    targetTime_ = targetTime;

    targetStartTime_ = time;
    targetStartAngle_ = angle_;

    Serial.println("Setting target");
    Serial.println(targetTime);
    Serial.println(time);
}

void MotorDriver::ZeroAngle(double position) {
    angle_ = position;
    target_ = position;
}

void MotorDriver::GetTimeToCompleteAngleChange(double da) {
    
}

void MotorDriver::Update(double time) {
    
}
