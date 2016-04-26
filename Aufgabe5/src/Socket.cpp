#include "Socket.h"


Socket::Socket()
{
}

Socket::~Socket()
{
}

bool Socket::write(const char* msg)
{
  if(nullptr == msg)
  {
    return false;
  }

  return true;
}
