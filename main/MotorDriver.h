#ifndef __MOTORDRIVER_H__
#define __MOTORDRIVER_H__

#include "Timer.hpp"

class MotorDriver{
public:
    MotorDriver(const Timer& timer);
    virtual ~MotorDriver();

    double GetAngle();
    virtual void SetVelocity(double angleVelocity);
    void ZeroAngle(double position = 0);

    virtual void Update();

protected:
    const Timer& timer_;

    double angle_;
    double angleVelocity_;

    // below this angle difference the driver will be satisfied
    double angleEpsilon_;
};

#endif // __MOTORDRIVER_H__