#include "EsMessage.h"


EsProtocol::Message::Message()
:m_Header{0,0,EsProtocol::Command::Invalid,0}
{
  // TODO tmp to be save from -Wunused..
  m_Header.payLoadLenght = 0;
}

EsProtocol::Message::~Message()
{}

EsProtocol::Command EsProtocol::Message::getCommand()
{
  return EsProtocol::Command::Invalid;
}

char* EsProtocol::Message::getRawData()
{
  return nullptr;
}

size_t EsProtocol::Message::getRawDataLength()
{
  return 0;
}
