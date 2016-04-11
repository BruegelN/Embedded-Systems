#include <iostream>

#include "Printf.h"

#define BUFFER_SIZE 50

int main(void)
{
  char buffer[BUFFER_SIZE] = {0};
  Printf(buffer, buffer+sizeof(buffer), "%sXXX%dXXX", "123", 123 );


  std::cout << "BUFFER: " << std::endl;
  for(int i = 0;  i < BUFFER_SIZE; i++)
  {
    std::cout << i << " is " << buffer[i] << std::endl;
  }

  return 0;

}
