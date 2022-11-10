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

void MotorDriver::SetTarget(double angle, double time) {
    target_ = angle;
    targetTime_ = time;
}

void MotorDriver::ZeroAngle(double position) {
    angle_ = position;
    target_ = position;
}

void MotorDriver::GetTimeToCompleteAngleChange(double da) {
    
}

void MotorDriver::Update(double time) {
    
}
