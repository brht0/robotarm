#include "MotorDriver.h"
#include "Arduino.h"

MotorDriver::MotorDriver(const Timer& timer):
	angle_(0.0), angleVelocity_(0.0), timer_(timer)
{
}

MotorDriver::~MotorDriver() {
}

double MotorDriver::GetAngle() {
	return angle_;
}

void MotorDriver::SetVelocity(double angleVelocity){
	angleVelocity_ = angleVelocity;
}

void MotorDriver::ZeroAngle(double position) {
	angle_ = position;
}

void MotorDriver::Update() {
}

bool MotorDriver::IsDone() const {
	return true;
}
