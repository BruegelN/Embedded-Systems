#include <iostream>

#include "SocketOptParser.h"
#include "UdpSocket.h" // TODO tmp, remove later

extern "C"
{
  #include <arpa/inet.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <netdb.h>
  #include <unistd.h>
}

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

  struct sockaddr_in otherSide;

  if(theParser.isServerMode())
  {
    // perform server task
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
  return 0;
}
