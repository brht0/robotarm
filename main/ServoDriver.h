#ifndef __SERVODRIVER_H__
#define __SERVODRIVER_H__

#include "MotorDriver.h"

#include <Servo.h>

class ServoDriver : public MotorDriver{
public:
    ServoDriver(int pin);
    ~ServoDriver();

    void init();
    
    virtual void Update(double time) override;

    void ZeroAngle(double position = 0);
    virtual void SetAngle(double angle) override;

private:
    int pin_;
    Servo servo_;

};

#endif // __SERVODRIVER_H__