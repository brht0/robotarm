#ifndef __EVENT_H__
#define __EVENT_H__

#include "Vector.h"
#include "MotorDriver.h"

struct Event{
    Vector<double> targets;
    Vector<MotorDriver*> drivers;

    Event();
    ~Event();

    bool IsDone() const;
    void AddEvent(MotorDriver* driver, double target);
    void SetEvents(double time, double targetTime);
};


#endif // __EVENT_H__