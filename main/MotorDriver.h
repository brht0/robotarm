#ifndef __MOTORDRIVER_H__
#define __MOTORDRIVER_H__

#include "Timer.hpp"

class MotorDriver{
public:
    MotorDriver(const Timer& timer);
    virtual ~MotorDriver();

    long double GetAngle();
    virtual void SetVelocity(long double angleVelocity);
    void ZeroAngle(long double position = 0);

    virtual void Update();

protected:
    const Timer& timer_;

    long double angle_;
    long double angleVelocity_;

    // below this angle difference the driver will be satisfied
    long double angleEpsilon_;
};

#endif // __MOTORDRIVER_H__