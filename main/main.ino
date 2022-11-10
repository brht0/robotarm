#include "RobotDriver.h"

ServoDriver servo1(9);
// ServoDriver servo2(5);

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
    
    servo1.SetTarget(0, GetTimeSeconds() + 0.1, GetTimeSeconds());
    delay(1000);
  }

bool flag1 = true;
bool flag2 = true;
bool flag3 = true;
void loop(){
    servo1.Update(GetTimeSeconds());
    delay(10);

    if((GetTimeSeconds() > 3.0) && flag1){
      flag1 = false;
      servo1.SetTarget(180, GetTimeSeconds() + 5.0, GetTimeSeconds());
    }
    
    if(GetTimeSeconds() > 10.0 && flag2){
      flag2 = false;
      servo1.SetTarget(0, GetTimeSeconds() + 4.0, GetTimeSeconds());
    }
    
    if(GetTimeSeconds() > 18.0 && flag3){
      flag3 = false;
      servo1.SetTarget(90, GetTimeSeconds() + 2.0, GetTimeSeconds());
    }
}
