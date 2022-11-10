#define _USE_MATH_DEFINES
#include <math.h> 

void angles(double height, double distance, double depth, double* res1, double* res2, double* res3) {
    double arm1 = 20.0;
    double arm2 = 15.0;

    
    double armH = height * height + distance * distance; // armH shorthand for h^2 + d^2

    // double a1tanIn = height / distance; 
    double a1cosIn = (arm1*arm1 - arm2 * arm2 + armH) / (2 * arm1 * sqrt(armH));
    double angle1 = atan2(height, distance) + acos(a1cosIn); // lower arm angle

    double a2cosIn = (arm1 * arm1 + arm2 * arm2 - armH) / (2 * arm1 * arm2); 
    double angle2 = acos(a2cosIn) - M_PI; // upper arm angle

    
    *res1 = angle1;
    *res2 = angle2;
    *res3 = atan2(distance, depth);
}

double toSteps(double angle, double perRevolution) {
    double steps = angle * perRevolution / (2 * M_PI);
    return steps;
}

class Motor{
public:
  Motor(int dirPin = 0, int stepPin = 0):
    dirPin(dirPin), stepPin(stepPin)
  {
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
  }
  //Motor& operator=(Motor&& rhs) = default;
  
  void zero(){ pos = desiredPos = 0; desiredTime = 1; }
  
  long getDelay(){
    long result = desiredTime / (abs(stepDistance) + 30);

    // clamp to range
    result = constrain(result, minDelay, maxDelay);
    
    return result;
  }

  void setTarget(long desiredPosition, long desiredTime){
    desiredPos = desiredPosition;
    this->desiredTime = desiredTime;
    stepDistance = desiredPos - pos;
  }

  void update(long t){
    long dpos = desiredPos - pos;
    long dir = (dpos > 0 ? 1 : (dpos == 0 ? 0 : -1));

    bool doStep = dpos != 0 && (t >= lastStepMicroS + getDelay());

    if(doStep){
      stepValue = stepValue == 0 ? 1 : 0;
      dirValue = dir > 0 ? 1 : 0;

      // set pin values
      digitalWrite(dirPin, dirValue);
      digitalWrite(stepPin, stepValue);

      // update stuff
      pos += dir;

      lastStepMicroS = t;
    }
  }
  
private:
  int dirPin, stepPin;
  int stepValue, dirValue;

  long pos, desiredPos, desiredTime = 999999999L, stepDistance = 0;
  long maxVelocity = 20L;

  long lastStepMicroS = 0;

  static const long minDelay = 1500;
  static const long maxDelay = 50000;

private:
  int getPosPinValue();
  int getDirPinValue();
};

class MotorDriver{
  public:
    MotorDriver(){
      motors[0] = Motor(3, 2); // rotation
      motors[1] = Motor(7, 6); // shoulder
      motors[2] = Motor(11, 10); // elbow
      
      motors[0].zero();
      motors[1].zero();
      motors[2].zero();
    }
  
    void setTarget(int index, long desiredPosition, long desiredTime){
      motors[index].setTarget(desiredPosition, desiredTime);
    }
  
    void update(){
      long t = micros();
      for(int i=0; i<3; i++){
        motors[i].update(t);
      }
    }

  private:
    Motor motors[3];
};

MotorDriver motors;


void setup() {
  Serial.begin(9600);

  // kulmat tähän
  double final1 = 0; //rotation
  double final2 = M_PI/2; //shoulder
  double final3 = 0; //elbow


  // älä koske
  long steps1 = toSteps(final1, 400UL);
  long steps2 = toSteps(final2, 24000UL);
  long steps3 = toSteps(final3, 4.4*400UL);

  unsigned long timeTo = 2000000;

  //prints stuff if stuff borken
  //Serial.println(steps1);
  //Serial.println(steps2);
  //Serial.println(res1);
  //Serial.println(res2);
  
  // motors.setTarget(0, 0, 1000000); // base
  // motors.setTarget(1, 0, 1000000); // shoulder
  // motors.setTarget(2, 400*5, 1000000); // elbow
  motors.setTarget(0, steps1, 1000000); // rotation
  motors.setTarget(1, steps2, 1000000); // shoulder
  motors.setTarget(2, steps3, 1000000); // elbow

  // delay for 0.2 seconds before doing anything
  delay(2000);
}


void loop() {
  motors.update();
  delayMicrosecondmvs(10);

  unsigned long timeTo = 2000000;
  unsigned long goBackTime = 9000000;
  
  static bool goneBack = false;
  
  if(!goneBack && micros() > goBackTime){
    motors.setTarget(0, 0, timeTo);
    motors.setTarget(1, 0, timeTo);
    motors.setTarget(2, 0, timeTo);
  }
}
