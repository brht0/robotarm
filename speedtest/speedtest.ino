int stepPin = 11;
int dirPin = 12;

void setup() {
  Serial.begin(9600);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  digitalWrite(dirPin, HIGH);

  delay(3000);
}

const unsigned long long max_delay_ms = 10000ULL;
unsigned long long delay_ms = max_delay_ms;
unsigned long long delay_interval = 2500ULL;

void loop() {
  delay(500);
  
  if(delay_ms < delay_interval || delay_ms> max_delay_ms){
    delay_ms = max_delay_ms;
  }

  Serial.print("Stepping with ");
  Serial.print((int)delay_ms);
  Serial.print(" delay\n");
  
  for(int i=0; i<1000000ULL/delay_ms; i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delay_ms);
    
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delay_ms);
  }

  delay_ms = delay_ms - delay_interval;
}
