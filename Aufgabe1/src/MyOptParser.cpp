#include <iostream> /* std::cout */
//#include <cstring> /* strncmp */

#include "MyOptParser.h"

MyOptParser::MyOptParser()
{
}

bool MyOptParser::option(char c, const char* info)
{
  if((c >= 48 && c <= 57 )||  // the value has to be in range 0-9
    (c >= 65 && c <= 90 ) ||  // or in range A-Z
    (c >= 97 && c <= 122))    // or in range a-z
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
    return false;
  }

}
