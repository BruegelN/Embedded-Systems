#include <iostream> /* std::cout */
#include <cstring> /* strncmp */

#include "OptParser.h"


CmdLineOptParser::CmdLineOptParser()
{
}

bool CmdLineOptParser::parse(int argc, const char **argv)
{
  if((2 <= argc) && argv != nullptr)
  {
    /* Skip over program name */
    argc--, argv++;

    for(int i=0; i<argc; i++)
    {
      std::cout
        << "\tNumber: " << i
        << "\tValue: " << argv[i]<< std::endl;

        const char* argumentOfInterest = argv[i];
        if(0 == strncmp(argumentOfInterest,"-x", 2))
        {
          std::cout << "-x given" << std::endl;
        }
    }
    return true;
  }
  else
  {
    std::cout << "Wrong number of arguments!" << std::endl;
    return false;
  }
}

bool CmdLineOptParser::option(char c, const char *info)
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
