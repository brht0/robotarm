#include "StepperDriver.h"
#include "Arduino.h"

StepperDriver::StepperDriver(const Timer& timer, int stepPin, int dirPin, ull stepsPerRevolution, ull minStepDelayMS) :
	MotorDriver(timer), stepPin_(stepPin), dirPin_(dirPin), stepsPerRevolution_(stepsPerRevolution), minStepDelayMS_(minStepDelayMS),
	stepDelayMs_(0), lastStepTime_(0), stepValue_(0), dirValue_(0), position_(0), stationary_(true)
{
}

StepperDriver::~StepperDriver() {
}

void StepperDriver::Update() {
	bool shouldStep = !stationary_ && timer_.GetTimeMS() - lastStepTime_ >= GetDelayMS();

	if(shouldStep){
		// whether motor should change step pin
		stepValue_ = stepValue_ == 0 ? 1 : 0;

		// change dir pin value
		dirValue_ = angleVelocity_ > 0.0 ? 1 : 0;

		// update pin values
		digitalWrite(dirPin_, dirValue_);
		digitalWrite(stepPin_, stepValue_);

		position_ += (dirValue_ == 1 ? 1 : -1) * stepValue_; 

		lastStepTime_ = timer_.GetTimeMS();
	}
}

void StepperDriver::SetVelocity(long double angleVelocity){
	MotorDriver::SetVelocity(angleVelocity);
	
  long double revolutionsPerSecond = ((long double)angleVelocity_ / (long double)(2.0*3.14159));
	long double stepsPerSecond = (long double)abs(revolutionsPerSecond) * (long double)stepsPerRevolution_;
	stepDelayMs_ = (long double)(10e7) / stepsPerSecond;

	stationary_ = (abs(revolutionsPerSecond) < 0.1);
	if(stepDelayMs_ < minStepDelayMS_) stepDelayMs_ = minStepDelayMS_; 

	// Serial.print((unsigned long)stepsPerSecond);
	// Serial.print(" ");
	// Serial.print((unsigned long)stepDelayMs_);
	// Serial.print("\n");
}

ull StepperDriver::GetDelayMS() const {
	return stepDelayMs_;
}

ull StepperDriver::GetPosition() const {
	return position_;    
}
