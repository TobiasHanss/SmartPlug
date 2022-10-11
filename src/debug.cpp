#include "Arduino.h"
#include "debug.h"

//************************************************************
//************************************************************
void qDebug(const char* format,...)
{
  char TextBuffer[50];
  va_list argv;
  va_start(argv, format);
  vsprintf(TextBuffer,format,argv);
  Serial.print(TextBuffer);
  va_end(argv);
}


void fail(const char* format,...) {
  char TextBuffer[50];
  va_list argv;
  va_start(argv, format);
  vsprintf(TextBuffer,format,argv);
  Serial.print(TextBuffer);
  va_end(argv);
  while (true) {
    yield();
  }
}