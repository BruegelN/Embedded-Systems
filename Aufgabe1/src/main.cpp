#include "OptParser.h"

int main( int argc, const char** argv)
{

  CmdLineOptParser theParser = CmdLineOptParser();

  return !theParser.parse(argc, argv);

}
