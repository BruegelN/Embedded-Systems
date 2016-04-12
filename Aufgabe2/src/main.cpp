#include <iostream>

#include "Printf.h"

#define BUFFER_SIZE 5

int main(void)
{
  char buffer[BUFFER_SIZE] = {0};
  char* test = Printf(buffer, buffer+sizeof(buffer), "%s","TESTTESTTEST");

  std::cout << "BUFFER: " << std::endl;
  for(int i = 0;  i < BUFFER_SIZE; i++)
  {
    std::cout << i << " is " << buffer[i] << std::endl;
  }

  std::cout << "next char to write: " << test << std::endl;

  return 0;

}
