#ifndef __STEPPERDRIVER_H__
#define __STEPPERDRIVER_H__

#include "MotorDriver.h"

class StepperDriver : public MotorDriver{
public:
    StepperDriver(int stepPin, int dirPin, int stepsPerRevolution);
    ~StepperDriver();

    virtual bool IsDone() const override;

    void init();
    
    virtual void Update(double time) override;

    void ZeroAngle(double position = 0);
    virtual void SetAngle(double angle) override;

private:
    double GetDelay() const;
    int AngleInSteps(double angle) const;

    int stepPin_, dirPin_;
    int stepValue = 0, dirValue = 0;

    long pos = 0;
    long stepDistance = 0;
    double maxAngleVelocity_ = 0.25 * 3.14159;

    int stepsPerRevolution_;

    double lastStepTime = 0;

    static const long minDelay = 1000;
    static const long maxDelay = 50000;

};

#endif // __STEPPERDRIVER_H__