#ifndef UDP_SOCKET_H
  #define UDP_SOCKET_H

#include <cstdint>
extern "C"
{
  #include <netinet/in.h> // struct sockaddr_in
}

class UdpSocket
{
public:
  // Creats a udp endpoint
  // CLIENTS-MODE: if no port is given it will listen on all port.
  // SERVER-MODE: provide a port No. to listen on
  UdpSocket(uint16_t portToListen = 0);
  ~UdpSocket();
  // TODO no copy constructor and asignment operator!
  bool hasBeenSuccessfullyCreated();
  // Takes the raw data to transfer
  // aswell as a junk of memory to return information about the other endpoint,
  // where to send the data to
  // returns true on succes.
  bool write(const char* data, size_t dataLenght, const struct sockaddr_in* destEndPointToWrite);
  // Reads data returned as char*.
  // Takes a struct sockaddr_in with infromations about where the data
  // are comming from.
  // If no
  bool read(char* buffer, size_t bufferLenght, struct sockaddr_in* destEndPointReadFrom = nullptr);
private:
  int m_FdSocket;
  struct sockaddr_in m_SockInLocal;
  bool m_bSuccessfullyCreated;
};

#endif // UDP_SOCKET_H
