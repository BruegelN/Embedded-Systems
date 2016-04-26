#include <iostream>

#include "SocketOptParser.h"

int main(int argc, const char** argv)
{

  SocketOptParser theParser = SocketOptParser();
  if(!theParser.parse(argc, argv))
  {
    // wrong usage, print help and exit
    std::cout << "Help for " << argv[0] << ":" << std::endl;
    std::cout << theParser.getHelpText() << std::endl;
    return 0;
  }

  if(theParser.isServerMode())
  {
    // perform server task
    

  }
  else
  {
    // running as client

  }
  return 0;
}
