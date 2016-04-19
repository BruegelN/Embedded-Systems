#ifndef CUSTOM_PRINTF_H
  #define CUSTOM_PRINTF_H
#include <cstdarg> /* va_list */

/*
* This is a modified version of the Printf function used previously!
* It't takes directly a va_list instead of the variadic arguments.
*/
char* Printf(char* dst, const void* end, const char* fmt, va_list arguements);


#endif // CUSTOM_PRINTF_H
