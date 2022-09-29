/*


A

B


- Needs to get from A to B in T time

steps = d(A,B)
time_per_step = T / steps




*/











class Motor{
public:
  Motor(int dirPin = 0, int stepPin = 0):
    dirPin(dirPin), stepPin(stepPin)
  {
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
  }
  //Motor& operator=(Motor&& rhs) = default;
  
  void zero(){ pos = 0; }
  
  long getDelay(){
    long result = desiredTime / abs(stepDistance);

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

  static const long minDelay = 800;
  static const long maxDelay = 50000;

private:
  int getPosPinValue();
  int getDirPinValue();
};

class MotorHandler{
public:
  MotorHandler(){
    motors[0] = Motor(11, 10);
    motors[1] = Motor(3, 2);
    motors[2] = Motor(7, 6);
    
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

MotorHandler motors;

void setup() {
  Serial.begin(9600);
  delay(250);

  // testing continuous rotation for 10 seconds
  motors.setTarget(0, 6000*400, 10000000);
}

void loop() {
  motors.update();
  delayMicroseconds(10);
}
