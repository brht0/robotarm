#ifndef __MOTORDRIVER_H__
#define __MOTORDRIVER_H__

/*
MotorDriver is an abstract class that will define pure virtual function
for handling angle of a specific motor type.

Different motors have different control mechanisms, hence this class
generalizes the usage of any motor with precision capabilities

All motors are expected to rotate linearly about a single plane
*/

class MotorDriver{
public:
    MotorDriver(double maxSpeed, double angleEpsilon);
    virtual ~MotorDriver();

    double GetAngle();

    // set angle to which motor should move in specified global time
    // note: motors have a max velocity (see GetTimeToCompleteAngleChange)
    void SetTarget(double angle, double targetTime, double time);

    // set current angle as given parameter
    void ZeroAngle(double position = 0);

    // specific motor types will override this function
    virtual void SetAngle(double angle) = 0;

    // returns an estimate of how long a motion will take according
    // to the maximum velocity of a motor
    void GetTimeToCompleteAngleChange(double da);

    // some motors require time dependent control (e.g. stepper motors)
    // this function can be overriden but not necessary
    virtual void Update(double time);

protected:
    double angle_;
    double maxSpeed_;

    double target_;
    double targetTime_;

    double targetStartAngle_;
    double targetStartTime_;

    // below this angle difference the driver will be satisfied
    double angleEpsilon_;
};

#endif // __MOTORDRIVER_H__