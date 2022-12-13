#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>

double ConvertToDouble(char* message){
  return atof(message);
}
double ConvertToDouble(String message){
  return atof(message.c_str());
}


#endif // __UTILS_H__