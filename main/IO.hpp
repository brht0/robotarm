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

  //String ReadCommand(){
  String ReadCommand(){
    bool done = false;
    //String currentToken = "";
    String resultString = "";
    
    while(Serial.available() > 0 && !done){
      char byte = Serial.read();

      resultString += byte;
  
      if(0)switch(byte){
        case '\n':
          //done = true;
          //result.push_back(currentToken);
          break;
        case ' ':
          //result.push_back(currentToken);
          //currentToken = "";
          break;
        default:
          //currentToken += byte;
          break;
      }
    }

    return resultString;
  }

private:
};

#endif // __IO_H__
