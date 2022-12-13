#ifndef __TIMER_H__
#define __TIMER_H__

#include "Arduino.h"

typedef unsigned long long ull;

class Timer{
public:
  Timer(){
    lastTime_ = micros();
  }

  double GetTimeSeconds(){
    return timeSeconds_;
  }

  double GetDeltaTimeSeconds(){
    return deltaTime_;
  }

  void Update(){
    ull newTime = micros();

    dt_ = newTime - lastTime_;
    lastTime_ = newTime;

    deltaTime_ = dt_ * (double)10e-7;
    timeSeconds_ = (lastTime_ - startTime_) * (double)10e-7;
  }

  void Reset(){
    ull newTime = micros();

    startTime_ = newTime;
    lastTime_ = newTime;
    dt_ = 0;
    timeSeconds_ = 0.0;
    deltaTime_ = 0.0;
  }

private:
  ull startTime_ = 0;
  ull lastTime_ = 0;
  ull dt_ = 0;
  
  double timeSeconds_ = 0;
  double deltaTime_ = 0;

};

#endif // __TIMER_H__
