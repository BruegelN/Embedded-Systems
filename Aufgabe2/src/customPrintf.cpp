#include "customPrintf.h"

char* Output::Printf(char *dst, const void *end, const char *fmt, ...)
{
  if(dst == nullptr || fmt == nullptr || fmt[0] != '%')
  {
    // invalid call
    return nullptr;
  }


  if('d' == fmt[1]) // %d signed int
  {

  }
  else if('u' == fmt[1]) // %u unsigned int
  {

  }
  else if('c' == fmt[1]) // %c char
  {

  }
  else if('s' == fmt[1]) // %s char[]
  {

  }
  else if('x' == fmt[1]) // %x 0x16
  {

  }
  else if('b' == fmt[1]) // %b b'110'
  {

  }

  return nullptr;
}
