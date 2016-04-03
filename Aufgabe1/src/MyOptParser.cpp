#include <iostream> /* std::cout */
//#include <cstring> /* strncmp */

#include "MyOptParser.h"

MyOptParser::MyOptParser()
{
}

bool MyOptParser::option(char c, const char* info)
{
  if((c >= '0' && c <= '9' )||  // the value has to be in range 0-9
    (c >= 'A' && c <= 'Z' ) ||  // or in range A-Z
    (c >= 'a' && c <= 'z'))    // or in range a-z
  {
    std::cout << "\tArgument: " << c << " given." << std::endl;
    if(nullptr != info)
    {
      std::cout << "\tValue: " << std::string(info) << std::endl;
    }
    else
    {
      std::cout << "\tNo value given." << std::endl;
    }

    return true;
  }
  else
  {
    std::cout << "\tInvalid option." << std::endl;
    return false;
  }

}
