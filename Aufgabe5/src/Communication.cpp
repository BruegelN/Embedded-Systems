extern "C"
{
  #include <arpa/inet.h> // inet_addr
}
#include <cstring> // mempcy
#include <iostream> // std::cout


#include "Communication.h"

namespace EsProtocol
{

Client::Client()
:m_TheServer{} // all field to zero
{
}

bool Client::init(const char* serverIpAddress, uint16_t serverPortNo)
{
  m_TheServer.sin_family = AF_INET;
  m_TheServer.sin_addr.s_addr = inet_addr(serverIpAddress);
  m_TheServer.sin_port = htons(serverPortNo);

  m_SockClient = UdpSocket();

  return m_SockClient.hasBeenSuccessfullyCreated();
}

Client::~Client()
{
  m_SockClient.~UdpSocket();
}

EsProtocol::Message& EsProtocol::Client::read()
{
  m_SockClient.read(m_Message.getMemoryToWrite(), m_Message.size(),&m_TheServer);
  return m_Message;;
}

bool EsProtocol::Client::write(EsProtocol::Message& theMessage)
{
  return m_SockClient.write(theMessage.getMemoryToWrite(), theMessage.size(),&m_TheServer);
}


Server::Server()
:m_theOtherSide{}, // all field to zero
m_Message{}
{
}

bool Server::init(uint16_t portToListen)
{
  m_SockServer = UdpSocket(portToListen);
  return m_SockServer.hasBeenSuccessfullyCreated();
}

Server::~Server()
{
  m_SockServer.~UdpSocket();
}

bool Server::run()
{
  if(m_SockServer.read(m_Message.getMemoryToWrite(), m_Message.size(), &m_theOtherSide) == false
    || !m_Message.isValidEOF()
    || m_Message.getChecksum() != m_Message.calcChecksum())
  {
    // trow away and skip over
    return true;
  }

  if(m_Message.getCommand() == EsProtocol::Command::Invalid)
  {
    // TODO or with Printf() with stdout?!
    std::cout << "Invalid command recieved" << std::endl;
  }
  else if(m_Message.getCommand() == EsProtocol::Command::Echo)
  {
    m_Message.setCommand(EsProtocol::Command::EchoReply);
    m_SockServer.write(m_Message.get(), m_Message.size(), &m_theOtherSide);
    return true;
  }
  else if(m_Message.getCommand() == EsProtocol::Command::Shutdown)
  {
    m_Message.setCommand(EsProtocol::Command::ShutdownReply);
    m_SockServer.write(m_Message.get(), m_Message.size(),&m_theOtherSide);
    return false; // break
  }
  // the other commands aren't handled by server thus try again
  return true;
}

void Server::shutdown()
{
  (*this).~Server();
}


} // namespace EsProtocol
