#include "OptParser.h"


CmdLineOptParser::CmdLineOptParser()
{
}

bool CmdLineOptParser::parse(int argc, const char **argv)
{
  if((1 <= argc) && argv != nullptr)
  {
    std::cout << "Given arguments:" << std::endl;
    for(int i=0; i<argc; i++)
    {
      std::cout
        << "\tNumber: " << i
        << "\tValue: " << argv[i]<< std::endl;
    }
    return true;
  }
  else
  {
    std::cout << "Wrong arguments!" << std::endl;
    return false;
  }
}

bool CmdLineOptParser::option(char c, const char *info)
{
  if((1 <= c) && (info != nullptr))
  {
    return true;
  }
  else
  {
    return false;
  }
}
