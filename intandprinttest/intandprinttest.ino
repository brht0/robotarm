void setup(){
  Serial.begin(9600);
}

void loop(){
  if(0){
    static unsigned long long counter = 0;
    counter += 1000000;
    Serial.println(counter);
  }
  else{
    Serial.println(micros());
  }
}
