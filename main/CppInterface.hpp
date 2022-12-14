#ifndef __IO_H__
#define __IO_H__

#include "Arduino.h"

class CppInterface{
public:
  CppInterface();
  
  void SetupSerial();
  String ReadCommand();

private:
  String commandSoFar_ = "";

};

#endif // __IO_H__
