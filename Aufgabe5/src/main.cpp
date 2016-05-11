//#define UDP_SOCKET_TEST

#include <iostream>

#include "SocketOptParser.h"
#include "UdpSocket.h"
#include "EsMessageCommand.h"
#include "EsMessageHeader.h"
#include "EsMessage.h"
#include "Communication.h"
/*
extern "C"
{
  #include <arpa/inet.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <netdb.h>
  #include <unistd.h>
}*/

int main(int argc, const char** argv)
{

  SocketOptParser theParser = SocketOptParser();
  if(!theParser.parse(argc, argv))
  {
    // wrong usage, print help and exit
    std::cout << "Help for " << argv[0] << ":" << std::endl;
    std::cout << theParser.getHelpText() << std::endl;
    return 0;
  }

#if 0
//defined(UDP_SOCKET_TEST)
  // udp socket test

  if(theParser.isServerMode())
  {
    // perform server task
    struct sockaddr_in otherSide;
    UdpSocket Server = UdpSocket(theParser.getPortNumber());
    std::cout << "Starting server at: " << theParser.getPortNumber() << std::endl;
    if(!Server.hasBeenSuccessfullyCreated())
    {
      std::cout << "can't create server" << std::endl;
      return 1;
    }
    while(1)
    {
      char input[2048] = "Hallo Welt";
      Server.read(input, strlen(input), &otherSide);
      std::cout << "Read: "<< input << " from " << inet_ntoa (otherSide.sin_addr) << ":"<< ntohs (otherSide.sin_port)  << std::endl;
      Server.write(input, strlen(input)+1, &otherSide);
    }

  }
  else
  {
    // running as client
    struct sockaddr_in otherSide;
    UdpSocket theClient = UdpSocket();
    std::cout << "Starting theClient to send on: "<< theParser.getIpAddrString() <<":" << theParser.getPortNumber() << std::endl;

    otherSide.sin_family = AF_INET;
    otherSide.sin_addr.s_addr = inet_addr(theParser.getIpAddrString());
    otherSide.sin_port = htons (theParser.getPortNumber());

    if(!theClient.hasBeenSuccessfullyCreated())
    {
      std::cout << "can't create theClient" << std::endl;
      return 1;
    }
    while(1)
    {
      char test[] = "Hallo Welt";

      std::cout << "Write: "<< theClient.write(test, strlen(test)+1,&otherSide) << " to " << inet_ntoa (otherSide.sin_addr) << ":"<< ntohs (otherSide.sin_port)  << std::endl;
      sleep(1);
      std::cout << "Reading echo: " << theClient.read( test, strlen(test),&otherSide) << std::endl;
      sleep(1);
    }
  }
#else
// more than udp socket test
  if(theParser.isServerMode())
  {

    EsProtocol::Server gServer; // = EsProtocol::Server();
    if(!gServer.init(theParser.getPortNumber()))
    {

      std::cout<< "Could not create server" << std::endl;
      return 1;
    }

    while(gServer.run())
    {
      // nothing just let the server run!
    }
    gServer.shutdown();
  }
  else
  {
    // running as client
    EsProtocol::Client gClient;
    if(!gClient.init(theParser.getIpAddrString(),theParser.getPortNumber()))
    {

      std::cout<< "Could not create client" << std::endl;
      return 1;
    }
    char test_str[] = "Test test";
    EsProtocol::Message aMessage(test_str, sizeof(test_str), EsProtocol::Command::Shutdown);
    // TODO client run

  }
#endif
//udp socket test

  return 0;
}
