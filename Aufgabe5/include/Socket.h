#ifndef BASE_SOCKET_H
  #define BASE_SOCKET_H

#include <cstdint>

/*
* Common Socket interface.
* Can be specialized for personal use.
* Eg. a TCP-Socket or RS232-Socket.
*/
class Socket
{
public:
  virtual bool hasBeenSuccessfullyCreated() = 0;
  virtual bool write(const char* data) = 0;
  virtual char* read() = 0;
};

#endif // BASE_SOCKET_H
