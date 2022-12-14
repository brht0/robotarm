#include "CppInterface.hpp"

#include "Arduino.h"

CppInterface::CppInterface(){}

void CppInterface::SetupSerial(){
    Serial.begin(9600);
    Serial.setTimeout(0);
}

String CppInterface::ReadCommand(){
    bool done = false;
    String result = "";

    while(Serial.available() > 0 && !done){
        char byte = Serial.read();

        if(byte == '\n'){
            result = commandSoFar_;
            commandSoFar_ = "";
        }
        else{
            commandSoFar_ += byte;
        }
    }

    return result;
}
