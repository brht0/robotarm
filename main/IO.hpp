#ifndef __IO_H__
#define __IO_H__

#include "Arduino.h"
#include "Vector.h"
#include "Timer.hpp"

class CppInterface{
public:
  CppInterface(){}
  ~CppInterface(){}

  void SetupSerial(){
    Serial.begin(9600);
    Serial.setTimeout(0);
  }

  String ReadCommand(){
    bool done = false;
    
    while(Serial.available() > 0 && !done){
      char byte = Serial.read();
  
      if(byte == '\n'){
        done = true;
      }
      else{
        commandSoFar += byte;
      }
    }

    if(done){
      // auto result = SplitToWords(commandSoFar);
      // Serial.println(commandSoFar);
      // Serial.println("Result: " + String(result.size()));
      auto result = commandSoFar;
      commandSoFar = "";
      return result;
    }
    else{
      // return Vector<String>();
      return "";
    }
  }

private:
  String commandSoFar = "";

  Vector<String> SplitToWords(const String& text){
    Vector<String> result;
    String word = String();

    for(char c : text){
      if(c == ' '){
        result.push_back(word);
        // Serial.println(word);
        word = String();
      }
      else{
        word += c;
      }
    }

    result.push_back(word);
    return result;
  }

};

#endif // __IO_H__
