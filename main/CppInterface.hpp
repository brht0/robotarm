#ifndef __IO_H__
#define __IO_H__

#include "Arduino.h"
#include "Vector.h"

class CppInterface{
public:
  CppInterface();
  
  void SetupSerial();
  String ReadCommand();

private:
  Vector<String> SplitToWords(const String& text);

  String commandSoFar_ = "";

} inline cppInterface;

#endif // __IO_H__
