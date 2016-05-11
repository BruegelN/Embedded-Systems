#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "UdpSocket.h"
#include "EsMessage.h"

namespace EsProtocol
{

class Client
{
public:
  Client();
  bool init(const char* serverIpAddress, uint16_t serverPortNo);
  ~Client();
  EsProtocol::Message& read();
  bool write(EsProtocol::Message&);
  // don't use these
  Client(const Client& old) = delete;
  Client& operator= (const Client& rhs) = delete;
private:
  UdpSocket m_SockClient;
  struct sockaddr_in m_TheServer;
  EsProtocol::Message m_Message;
  void shutdown();

};

class Server
{
public:
  Server();
  bool init(uint16_t portToListen);
  ~Server();
  // it't not usefull if the server can "write on it's own"
  // thus don't provide a write or read method
  bool run();
  // close the socket
  void shutdown();
  // don't use these
  Server(const Server& old) = delete;
  Server& operator= (const Server& rhs) = delete;
private:
  UdpSocket m_SockServer;
  struct sockaddr_in m_theOtherSide;
  EsProtocol::Message m_Message;
};

} // namespace EsProtocol

#endif // COMMUNICATION_H
