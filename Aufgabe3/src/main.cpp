#include <iostream>

#include "PreAllocString.h"


int main(void) {

  PreAllocString<11> test;
  test = "test";
  test += '3';
  test.AddWhiteSpace();
  test += "adsf";
  test += '3';

  size_t lenght = test.GetLength();
  size_t buffersize = test.SizeOf();

  std::cout << "Strlen is: " << lenght << std::endl;
  std::cout << "Template buffersize is: " << buffersize << std::endl;

  // test 1 = char
  char test1 = 'N';
  test = test1;
  std::cout << "Test1 = char " << std::endl;
  for(size_t i = 0;  i < lenght+4; i++)
  {
    std::cout << i << " is " << test[i] << std::endl;
  }
  std::cout << std::endl << std::endl;


  // testing = const char*
  const char test2[] = "const char*";
  test = reinterpret_cast<const char*>(test2);
  std::cout << "Test2 = const char* " << std::endl;
  for(size_t i = 0;  i < lenght+4; i++)
  {
    std::cout << i << " is " << test[i] << std::endl;
  }
  std::cout << std::endl << std::endl;


  // testing = char* const
  char test3[] = "char* const";
  test = reinterpret_cast<char* const>(test3);
  std::cout << "Test3 = char* const " << std::endl;
  for(size_t i = 0;  i < lenght+4; i++)
  {
    std::cout << i << " is " << test[i] << std::endl;
  }
  std::cout << *(test) <<std::endl << std::endl;

  // testing +=
  test.Empty();
  test = test1; // just a char
  test.AddWhiteSpace();
  char test4[] = "hallo";
  test += reinterpret_cast<char* const>(test4);
  std::cout << "Test2 = char* const " << std::endl;
  for(size_t i = 0;  i < lenght+4; i++)
  {
    std::cout << i << " is " << test[i] << std::endl;
  }
  std::cout << std::endl << std::endl;



  return 0;
}
