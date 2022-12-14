#include "StepperDriver.h"
#include "Arduino.h"

StepperDriver::StepperDriver(const Timer& timer, int stepPin, int dirPin, ull stepsPerRevolution) :
	MotorDriver(timer), stepPin_(stepPin), dirPin_(dirPin), stepsPerRevolution_(stepsPerRevolution),
	stepDelayMs_(0), lastStepTime_(0), stepValue_(0), dirValue_(0), position_(0)
{
}

StepperDriver::~StepperDriver() {
}

void StepperDriver::Update() {
	bool shouldStep = timer_.GetTimeMS() - lastStepTime_ >= GetDelayMS();

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

// #include "Arduino.h"

void StepperDriver::SetVelocity(long double angleVelocity){
	MotorDriver::SetVelocity(angleVelocity);
	
	// if(abs(angleVelocity_) < 0.1){
	// 	stepDelayMs_ = 10e14;
	// 	return;
	// }

	// 200 steps per rev
	// 2pi velocity
	// -> 200 per second
	// pi velocity
	// -> 100 per second
	long long stepsPerSecond = (long double)stepsPerRevolution_ * (long double)angleVelocity_ / (long double)(2.0*3.14159);
	stepDelayMs_ = (unsigned long)stepsPerSecond * 10e9;

	Serial.print((unsigned long)stepsPerSecond);
	Serial.print(" ");
	Serial.print((unsigned long)stepDelayMs_);
	Serial.print("\n");

}

ull StepperDriver::GetDelayMS() const {
	return stepDelayMs_;
}

ull StepperDriver::GetPosition() const {
	return position_;    
}
