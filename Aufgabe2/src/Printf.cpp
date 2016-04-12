#include <cstdarg>
#include <cstdbool>
#include <cstdlib> /* size_t */

#include "Printf.h"

/* Helper functions */
static bool isEnoughFreeSpaceInBuffer(char* dst, const void* end, size_t nBytes);
/**
* use pointer to char* to decrease the buffer automaticly whenever a char is placed in buffer.
*/
static void putCharInBuffer(char** dstAddr, char value);
static char* uintToChars(unsigned int value, char** dstAddr, const void* end);

// TODO
static char* tmpReturnValue = nullptr;

char* Printf(char *dst, const void *end, const char *fmt, ...)
{
  if(dst == nullptr || fmt == nullptr || end == nullptr || end < dst )
  {
    // invalid call
    return nullptr;
  }

  va_list arguments;
  va_start(arguments, fmt);

  // increment allways by one
  // everytime %*key* is detected an additional incrementation is needed!
  for(int argCount = 0; fmt[argCount] != '\0';argCount++)
  {
    if('%' == fmt[argCount])
    {
      switch (fmt[argCount+1]) {
        // %d signed int
        case 'd':
        {
          ++argCount;
          signed int value  = va_arg(arguments,signed int);
          unsigned int positiveValue;
          if( value < 0)
          {
            positiveValue = std::abs(value);
            if(isEnoughFreeSpaceInBuffer(dst, end,sizeof(char)))
            {
              putCharInBuffer(&dst, '-');
            }
            else
            {
              *tmpReturnValue = '-';
              return tmpReturnValue;
            }
          }
          else
          {
            positiveValue = value;
          }

          char* returnPointer = uintToChars(positiveValue, &dst, end);
          if(returnPointer != nullptr)
          {
            // return first not printable char
            *tmpReturnValue = *returnPointer;
            return tmpReturnValue;
          }
          break;
        }

        // %u unsigned int
        case 'u':
        {
          ++argCount;
          unsigned int value  = va_arg(arguments, unsigned int);
          // For every digit a char is needed!
          char* returnPointer = uintToChars(value, &dst, end);
          if(returnPointer != nullptr)
          {
            // return first not printable char
            *tmpReturnValue = *returnPointer;
            return tmpReturnValue;
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
            putCharInBuffer(&dst, value);
          }
          else
          {
            // ptr to next single char
            *tmpReturnValue = value;
            return tmpReturnValue;
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
              putCharInBuffer(&dst, *value);
            }
            else
            {
              // ptr to next char
              *tmpReturnValue = *value;
              return tmpReturnValue;
            }
            value++;
          }
          break;
        }

        // %x 0x16
        case 'x':
        {
          ++argCount;
          // for look up
          static char hexchars[] = "0123456789ABCDEF";

          // NOTE uint32_t is not guarantued to be unsigned int on all platforms!
          // So you might run into some issues when you try to convert bigger numbers, thus you have to change this to uint64_t and adopt the converstion below.
          uint32_t value  = va_arg(arguments,uint32_t);
          if(isEnoughFreeSpaceInBuffer(dst, end, 8+2)) // because 32/4(=sizeof(nibble) == 8 + 2 for 0x)
          {
            // for uint32_t and hex values it's clear without a loop
            dst[0] = '0';
            dst[1] = 'x';
            dst[2] = hexchars[value >> 28 & 0xF];
            dst[3] = hexchars[value >> 24 & 0xF];
            dst[4] = hexchars[value >> 20 & 0xF];
            dst[5] = hexchars[value >> 16 & 0xF];
            dst[6] = hexchars[value >> 12 & 0xF];
            dst[7] = hexchars[value >>  8 & 0xF];
            dst[8] = hexchars[value >>  4 & 0xF];
            dst[9] = hexchars[value       & 0xF];
            // manualy decrease buffer!!!
            dst += 10;
          }
          else
          {
            // the first char of our hex value
            *tmpReturnValue = hexchars[value >> 28];
            return tmpReturnValue;
          }
          break;
        }
        // %b b'110'
        case 'b':
        {
          ++argCount;
          uint32_t value  = va_arg(arguments,uint32_t);
          // place a 'b' before every binary number
          if(isEnoughFreeSpaceInBuffer(dst, end, sizeof(char)))
          {
            putCharInBuffer(&dst, 'b');
          }
          else
          {
            *tmpReturnValue = 'b';
            return tmpReturnValue;
          }

          // for look up
          static char binarychars[] = "01";
          // remember that we found a one, which allows us to drop leading zeros
          bool foundOne = false;
          // iterate bit by bit over number
          for(int position = 31; position>= 0; position--)
          {
            char tmpChar = binarychars[value >> position & 0x1];
            if(tmpChar == '0' && foundOne == false)
            {
              // skip over leading zeros!
              continue;
            }
            // else do the following and remember that there has been a one
            foundOne = true;
            if(isEnoughFreeSpaceInBuffer(dst, end, sizeof(char)))
            {
              putCharInBuffer(&dst, tmpChar);
            }
            else
            {
              *tmpReturnValue = tmpChar;
              return tmpReturnValue;
            }
          }
          break;
        }
        default:
          // if '%' isn't followd by a known command then we should
          // print the percent symbol e.g. 100%
          if(isEnoughFreeSpaceInBuffer(dst, end,sizeof(char)))
          {
            putCharInBuffer(&dst, '%');
          }
          else
          {
            *tmpReturnValue = '%';
            return tmpReturnValue;
          }
          break;
      }
    }
    else
    {
      if(isEnoughFreeSpaceInBuffer(dst, end,sizeof(char)))
      {
        putCharInBuffer(&dst, fmt[argCount]);
      }
      else
      {
        // last char
        *tmpReturnValue = fmt[argCount];
        return tmpReturnValue;
      }
    }
  }
  va_end(arguments);

  return nullptr;
}

static bool isEnoughFreeSpaceInBuffer(char* dst, const void* end, size_t nBytes)
{
  if(dst + nBytes > end)
  {
    return false;
  }
  else
  {
    return true;
  }
}

static void putCharInBuffer(char** dstAddr, char value)
{
  if(dstAddr == nullptr || *dstAddr == nullptr)
  {
    return;
  }
  (*dstAddr)[0] = value;
  (*dstAddr) = *dstAddr +1;
}

static char* uintToChars(uint32_t value, char** dstAddr, const void* end)
{
  // http://www.cplusplus.com/articles/D9j2Nwbp/#bad

  uint32_t tmpValue = value;
  size_t digits = 0;
  while(tmpValue != 0)
  {
    tmpValue /= 10;
    digits++;
  }

  // because array starts a [0]
  size_t positons = digits-1;
  if(dstAddr == nullptr || *dstAddr == nullptr || end == nullptr || !isEnoughFreeSpaceInBuffer(*dstAddr,end, positons))
  {
    *tmpReturnValue = tmpValue+'0';
    return tmpReturnValue;
  }
  else
  {

    do
    {
      // generate digits in reverse order
      (*dstAddr)[positons--] = static_cast<char>(value % 10 + '0');   // get next digit
    } while ((value /= 10) > 0); // digit added thus head over to the next one

    // decrease buffer
    (*dstAddr) = *dstAddr + digits;
  }
  return nullptr;
}
