#ifndef __STEPPERDRIVER_H__
#define __STEPPERDRIVER_H__

#include "MotorDriver.h"

class StepperDriver : public MotorDriver{
public:
    StepperDriver(const Timer& timer, int stepPin, int dirPin, ull stepsPerRevolution, ull minStepDelayMS);
    ~StepperDriver();

    ull GetPosition() const;

    virtual void SetVelocity(long double angleVelocity) override;
    virtual void Update() override;

private:
    ull GetDelayMS() const;

    ull stepsPerRevolution_;
    long long position_;

    bool stationary_;
    ull stepDelayMs_;
    ull lastStepTime_;

    int stepPin_, dirPin_;
    int stepValue_ = 0, dirValue_ = 0;

    ull minStepDelayMS_;
};

#endif // __STEPPERDRIVER_H__