#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include "Arduino.h"

double ConvertToDouble(char* message){
  return atof(message);
}

double ConvertToInt(char* message){
  return atoi(message);
}

double ConvertToDouble(const String& message){
  return atof(message.c_str());
}

double ConvertToInt(const String& message){
  return atoi(message.c_str());
}

#endif // __UTILS_H__