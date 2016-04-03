#include "MyOptParser.h"

int main( int argc, const char** argv)
{

  MyOptParser theParser = MyOptParser();

  return !theParser.parse(argc, argv);

}
