#include <cstdarg>
#include <cstdbool>
#include <cstdlib> /* size_t */
#include <cstdio>

// TODO
#include <iostream>

#include "Printf.h"

/* Helper functions */
static bool isEnoughFreeSpaceInBuffer(char* dst, const void* end, size_t nBytes);
static void putCharInBuffer(char* dst, char value);
static size_t getBytesCountOfInt(unsigned int value, int base);
//static void reduceRemainingBufer(char **dst, size_t nBytes);

// TODO not c++ style but quick fix
static unsigned int positionInBuffer;

char* Printf(char *dst, const void *end, const char *fmt, ...)
{
  if(dst == nullptr || fmt == nullptr || end == nullptr  || fmt[0] != '%')
  {
    // invalid call
    return nullptr;
  }


  va_list arguments;
  va_start(arguments, fmt);

  // increment allways by one
  // everytime %*key* is detected an additional inkrementation is needed!
  for(int argCount = 0; fmt[argCount] != '\0';argCount++)
  {
    std::cout << argCount << " elem is: " <<fmt[argCount] << std::endl;
    if('%' == fmt[argCount])
    {
      switch (fmt[argCount+1]) {
        // %d signed int
        case 'd':
        {
          ++argCount;
          signed int value  = va_arg(arguments,signed int);
          if( value < 0)
          {
            value = std::abs(value);
            if(isEnoughFreeSpaceInBuffer(dst, end,sizeof(char)))
            {
              putCharInBuffer(dst, '-');
            }
          }
          // For every digit a char is needed!
          size_t digits = getBytesCountOfInt(value, 10);
          if(isEnoughFreeSpaceInBuffer(dst, end, digits))
          {
            positionInBuffer += snprintf(&dst[positionInBuffer], digits+1, "%d", value);
          }
          break;
        }

        // %u unsigned int
        case 'u':
        {
          unsigned int value  = va_arg(arguments, unsigned int);
          // For every digit a char is needed!
          size_t digits = getBytesCountOfInt(value, 10);
          if(isEnoughFreeSpaceInBuffer(dst, end, digits))
          {
            positionInBuffer += snprintf(&dst[positionInBuffer], digits+1, "%d", value);
          }

          break;
        }
        // %c char
        case 'c':
        {
          ++argCount;
          // This is weird because va_arg doesn't accept char as type!
          char value = va_arg(arguments, int);
          if(isEnoughFreeSpaceInBuffer(dst, end,sizeof(char)))
          {
            putCharInBuffer(dst, value);
          }
          else
          {
            // TODO
          }
          break;
        }
        // %s string/char[]
        case 's':
        {
          ++argCount;
          char* value = va_arg(arguments, char*);
          while (*value != '\0')
          {
            if(isEnoughFreeSpaceInBuffer(dst, end,sizeof(char)))
            {
              putCharInBuffer(dst, *value);
            }
            value++;
          }
          break;
        }

        // %x 0x16
        case 'x':
        {
          ++argCount;
          signed int value  = va_arg(arguments,signed int);
          if( value < 0)
          {
            value = std::abs(value);
            if(isEnoughFreeSpaceInBuffer(dst, end,sizeof(char)))
            {
              putCharInBuffer(dst, '-');
            }
          }
          // For every digit a char is needed!
          size_t digits = getBytesCountOfInt(value, 16);
          if(isEnoughFreeSpaceInBuffer(dst, end, digits+1))
          {
            // add two extra bytes fo '0x'
            positionInBuffer += snprintf(&dst[positionInBuffer], digits+1+2, "0x%x", value);
          }
          break;
        }
        // %b b'110'
        case 'b':
        {
          //TODO
          /*++argCount;
          signed int value  = va_arg(arguments,signed int);
          if( value < 0)
          {
            value = std::abs(value);
            if(isEnoughFreeSpaceInBuffer(dst, end,sizeof(char)))
            {
              putCharInBuffer(dst, '-');
            }
          }
          // For every digit a char is needed!
          size_t digits = getBytesCountOfInt(value, 2);
          if(isEnoughFreeSpaceInBuffer(dst, end, digits))
          {
            positionInBuffer += snprintf(&dst[positionInBuffer], digits+1, "%b", value);
          }*/
          break;
        }
        default:
          // if '%' isn't followd by a known command then we should
          // print the percent symbol e.g. 100%
          if(isEnoughFreeSpaceInBuffer(dst, end,sizeof(char)))
          {
            putCharInBuffer(dst, '%');
          }
          break;
      }
    }
    else
    {
      if(isEnoughFreeSpaceInBuffer(dst, end,sizeof(char)))
      {
        putCharInBuffer(dst, fmt[argCount]);
      }
    }
  }
  va_end(arguments);
  return nullptr;
}

static bool isEnoughFreeSpaceInBuffer(char* dst, const void* end, size_t nBytes)
{
  if(&dst[positionInBuffer] + nBytes > end)
  {
    return false;
  }
  else
  {
    return true;
  }
}

static void putCharInBuffer(char* dst, char value)
{
  if(dst == nullptr)
  {
    return;
  }
  dst[positionInBuffer] = value;
  positionInBuffer++;
}

static size_t getBytesCountOfInt(unsigned int value, int base)
{
  size_t digits = 0;
  while( value != 0 )
  {
   value /= base;
   digits++;
  }
  return digits;
}
