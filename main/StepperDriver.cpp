#include "StepperDriver.h"

#include "Arduino.h"

StepperDriver::StepperDriver(int stepPin, int dirPin, int stepsPerRevolution) :
    MotorDriver(90.f, 3.f), stepPin_(stepPin), dirPin_(dirPin), stepsPerRevolution_(stepsPerRevolution)
{
}

StepperDriver::~StepperDriver() {
}

bool StepperDriver::IsDone() const{
    return abs(angle_ - AngleInSteps(target_)) <= 0.03;
}

void StepperDriver::init() {
    ZeroAngle();
}

void StepperDriver::Update(double time) {
    long dpos = AngleInSteps(target_) - pos;
    long dir = (dpos > 0 ? 1 : (dpos == 0 ? 0 : -1));

    bool doStep = dpos != 0 && (time > lastStepTime + GetDelay());

    //Serial.print("Before step...");
    //Serial.print(target_);
    //Serial.print("\n");

    if(doStep){
        if(0){
            Serial.print("Stepping...");
            Serial.print(pos);
            Serial.print(" ");
            Serial.print(angle_);
            Serial.print(" ");
            Serial.print(dirValue);
            Serial.print("\n");
        } 
        stepValue = stepValue == 0 ? 1 : 0;
        dirValue = dir > 0 ? 1 : 0;

        // set pin values
        digitalWrite(dirPin_, dirValue);
        digitalWrite(stepPin_, stepValue);

        // update stuff
        pos += dir;

        lastStepTime = time;
        angle_ = pos / (double)stepsPerRevolution_;
    }

}

void StepperDriver::ZeroAngle(double position) {
    pos = 0;
    angle_ = 0;
}

void StepperDriver::SetAngle(double angle) {
    angle_ = angle;
    //setTargetOld(angle * stepsPerRevolution, 1.0 * 10e6);
}

int StepperDriver::AngleInSteps(double angle) const {
    return angle * stepsPerRevolution_;    
}

double StepperDriver::GetDelay() const {
    //return 0.0001;
    return (targetTime_ - targetStartTime_) / (double)stepsPerRevolution_;

    //long result = max(targetTime_ - targetStartTime_, 0) / (abs(stepDistance) + 30);

    // clamp to range
    //result = constrain(result, minDelay, maxDelay);

    //return result;
}
