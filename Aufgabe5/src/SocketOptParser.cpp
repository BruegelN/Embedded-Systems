#include <iostream> // std::cout
#include <cstdlib> //strtol

#include "SocketOptParser.h"

SocketOptParser::SocketOptParser()
: m_bServerMode{false}
, m_u32PortNumber{0}
, m_strIpAddress{nullptr}
{
}

const char* SocketOptParser::getHelpText()
{
  return  "\t-s for server mode\n"
          "\t-p for port number\n"
          "\t-i for the ip-address to connect to\n"
          "\tEither call it in server mode or "
          "provide an ip-address for client mode!\n";
}

bool SocketOptParser::option(char c, const char* info)
{

  // In servermode no IP Address needed!
  if('s' == c && m_strIpAddress == nullptr)
  {
    // use it in servermode
    m_bServerMode = true;
    return true;
  }
  else if('p' == c &&  info != nullptr)
  {
    // using old C-Style strtol is guaranteed not to throw an exception
    m_u32PortNumber = static_cast<uint32_t>(strtoul(info, (char **)NULL, 10));
    return true;
  }
  else if('i' == c && info != nullptr && !m_bServerMode)
  {
    m_strIpAddress = strdup(info);
    return true;
  }
  else
  {
    return false;
  }
}

bool SocketOptParser::isServerMode() const
{
  return m_bServerMode;
}

uint32_t SocketOptParser::getPortNumber() const
{
  return m_u32PortNumber;
}

const char* SocketOptParser::getIpAddrString() const
{
  return m_strIpAddress;
}
