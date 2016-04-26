#ifndef MY_SOCKET_H
  #define MY_SOCKET_H

class Socket
{
public:
  Socket();
  ~Socket();
  bool write(const char*);
};

#endif // MY_SOCKET_H
