extern "C"
{
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <unistd.h> // close() sys-call
}

#include "UdpSocket.h"


UdpSocket::UdpSocket(uint16_t portToListen)
:
m_SockInLocal{}, // auto-init all fields with zero
m_bSuccessfullyCreated{true}
{
  if((m_FdSocket = socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP)) == -1)
  {
    m_bSuccessfullyCreated = false;
  }
  else
  {
    m_SockInLocal.sin_family = AF_INET;
    m_SockInLocal.sin_port = htons(portToListen);
    m_SockInLocal.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(m_FdSocket, (struct sockaddr *)&m_SockInLocal, sizeof(m_SockInLocal))==-1)
    {
      m_bSuccessfullyCreated = false;
    }
  }
}

UdpSocket::~UdpSocket()
{
  // close file descriptor for socket
  close(m_FdSocket);
}

bool UdpSocket::hasBeenSuccessfullyCreated()
{
  return m_bSuccessfullyCreated;
}

bool UdpSocket::write(const char* data, size_t dataLenght, const struct sockaddr_in* destEndPointToWrite)
{
  if(data == nullptr || destEndPointToWrite == nullptr)
  {
    return false;
  }

  if(sendto(m_FdSocket, data, dataLenght, 0,
            reinterpret_cast<const struct sockaddr *>(destEndPointToWrite),
            sizeof(*destEndPointToWrite)
          ) < 0)
  {
    // unable to send data to how ever don't set pointers to nullptr
    // thus caller might check what's wrong
    return false;
  }
  // fire and forget
  return true;
}

bool UdpSocket::read(char* buffer, size_t bufferLenght, struct sockaddr_in* destEndPointReadFrom)
{
  if(buffer == nullptr || bufferLenght == 0)
  {
    return false;
  }

  if(destEndPointReadFrom == nullptr)
  {
    // use m_SockInLocal aka "server-mode"
    // tmp workaround because recvfrom takes a pointer to lenght...
    socklen_t tmpLenght =  sizeof(m_SockInLocal);
    if (recvfrom(m_FdSocket, buffer, bufferLenght, 0,
                reinterpret_cast<struct sockaddr *>(&m_SockInLocal),
                &tmpLenght
              )< 0)
    {
      return false;
    }
  }
  else
  {
    // use the provided informations of the end point.
    // tmp workaround because recvfrom takes a pointer to lenght...
    socklen_t tmpLenght =  sizeof(*destEndPointReadFrom);
    if (recvfrom(m_FdSocket, buffer, bufferLenght, 0,
                  reinterpret_cast<struct sockaddr *>(destEndPointReadFrom),
                  &tmpLenght
                )< 0)
    {
      return false;
    }
  }

  // it looks like it worked
  return true;
}
