#include "Timer.hpp"

Timer::Timer():
  startTime_(0),
  lastTime_(0),
  timeSeconds_(0),
  deltaTime_(0),
  timeSecondsMS_(0),
  deltaTimeMS_(0)
{
}

ull Timer::GetTimeMS() const {
  return timeSecondsMS_;
}

ull Timer::GetDeltaTimeMS() const {
  return deltaTimeMS_;
}

double Timer::GetTimeSeconds() const {
  return timeSeconds_;
}

double Timer::GetDeltaTimeSeconds() const {
  return deltaTime_;
}

void Timer::Update(){
  ull newTime = micros();

  deltaTimeMS_ = newTime - lastTime_;
  timeSecondsMS_ = newTime;

  deltaTime_ = deltaTimeMS_ * (long double)10e-7;
  timeSeconds_ = deltaTimeMS_ * (long double)10e-7;
}

void Timer::Reset(){
  ull newTime = micros();

  startTime_ = newTime;
  lastTime_ = newTime;

  timeSeconds_ = 0.0;
  timeSecondsMS_ = 0;
  deltaTime_ = 0.0;
  deltaTimeMS_ = 0;
}
