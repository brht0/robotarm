#include "CppInterface.hpp"

#include "Arduino.h"
#include "Vector.h"

CppInterface(){}

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

Vector<String> CppInterface::SplitToWords(const String& text){
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
