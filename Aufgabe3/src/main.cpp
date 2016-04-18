#include <iostream>

#include "PreAllocString.h"


int main(void) {

  PreAllocString<20> test;
  test = "test";
  test += '3';
  test.AddWhiteSpace();
  test += "adsf";
  test += '3';

  size_t lenght = test.GetLength();

  std::cout << "Strlen is: " << lenght << std::endl;
  for(size_t i = 0;  i < lenght; i++)
  {
    std::cout << i << " is " << test[i] << std::endl;
  }

  return 0;
}
