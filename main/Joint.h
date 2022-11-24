#ifndef __JOINT_H__
#define __JOINT_H__

#include "ServoDriver.h"
#include "StepperDriver.h"

/*
Joint has a single motor connected to it and a specified length,
therefore I decided to do it this way since it's the way it is.
*/

#include "Vector.h"

class Joint{
public:
    Joint();
    Joint(double length, MotorDriver* driver);
    ~Joint();

    void Update(double time);

    double GetLength() const;
    double GetAngle() const;
    Vector<double> GetPositionChange() const;

    void SetTarget(double angle, double targetTime, double time);
    void SetAngle(double angle);

private:
    double length_;

    MotorDriver* driver_;

};

#endif // __JOINT_H__