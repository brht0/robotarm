#include "MotorDriver.h"
#include "Arduino.h"

MotorDriver::MotorDriver(const Timer& timer):
	angle_(0.0), angleVelocity_(0.0), timer_(timer)
{
}

MotorDriver::~MotorDriver() {
}

long double MotorDriver::GetAngle() {
	return angle_;
}

void MotorDriver::SetVelocity(long double angleVelocity){
	angleVelocity_ = angleVelocity;
}

void MotorDriver::ZeroAngle(long double position) {
	angle_ = position;
}

void MotorDriver::Update() {
}
