#include <iostream>

#include "SocketOptParser.h"

int main(int argc, const char** argv)
{

  SocketOptParser theParser = SocketOptParser();
  if(!theParser.parse(argc, argv))
  {
    // TODO return with help text
    std::cout << "Help for " << argv[0] << ":" << std::endl;
    std::cout << theParser.getHelpText() << std::endl;
  }
  return 0;
}
