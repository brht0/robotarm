#include "RobotDriver.h"
#include "Event.hpp"

ServoDriver servo1(9);
// ServoDriver servo2(5);

StepperDriver stepper1(11, 10, 550);
StepperDriver stepper2(6, 7, 7200);
StepperDriver stepper3(2, 3, 130);

int eventIndex = 0;
Vector<Event> events;

int startTime;
bool first = true;
double GetTimeSeconds(){
  if(first){
    startTime = millis();
    first = false;
  }
  return (millis() - startTime) * 10e-4;
}

void setup(){
    Serial.begin(9600);

    servo1.init();
    // servo2.init();
    stepper1.init();
    stepper2.init();
    stepper3.init();

    Event e0;
    //e0.AddEvent(&servo1, 180.0);
    e0.AddEvent(&stepper1, -0.1 * 3.14159);
    //e0.AddEvent(&stepper2, 0.1 * 3.14159);
    //e0.AddEvent(&stepper3, 0.1 * 3.14159);

    events.push_back(e0);

    delay(500);
    auto t = GetTimeSeconds();
    events[0].SetEvents(t, t+10.0);
    
    //servo1.SetTarget(0, GetTimeSeconds() + 0.1, GetTimeSeconds());
}

bool flag1 = true;
bool flag2 = true;
bool flag3 = true;

void loop(){
    //servo1.Update(GetTimeSeconds());
    auto t = GetTimeSeconds();

    stepper1.Update(t);
    stepper2.Update(t);
    stepper3.Update(t);
    //servo1.Update(t);

    if(events[eventIndex].IsDone()){
      Serial.println("Event done");
      eventIndex ++;
      events[eventIndex].SetEvents(t, t + 10.0);
    }
    else{
      if(eventIndex >= events.size()){
        //Serial.println("Event done");
      }
    }

    //delay(10);
}
