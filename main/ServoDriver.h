#ifndef __SERVODRIVER_H__
#define __SERVODRIVER_H__

#include "MotorDriver.h"

#include <Servo.h>

class ServoDriver : public MotorDriver{
public:
    ServoDriver(const Timer& timer, int pin);
    ~ServoDriver();
    
    virtual void Update() override;

private:
    bool pinAttached;
    void AttachPin();

    int pin_;
    Servo servo_;
    long double position_;
    
    const long double maxPosition_ = 180.0;
    const long double minPosition_ = 0.0;
};

#endif // __SERVODRIVER_H__