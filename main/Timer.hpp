#ifndef __TIMER_H__
#define __TIMER_H__

#include "Arduino.h"

typedef unsigned long long ull;

class Timer{
public:
  Timer();

  void Update();
  void Reset();
  
  double GetTimeSeconds() const;
  double GetDeltaTimeSeconds() const;
  ull GetTimeMS() const;
  ull GetDeltaTimeMS() const;
  
private:
  ull startTime_ = 0;
  ull lastTime_ = 0;
  
  long double timeSeconds_ = 0;
  long double deltaTime_ = 0;
  ull timeSecondsMS_ = 0;
  ull deltaTimeMS_ = 0;
};

#endif // __TIMER_H__
