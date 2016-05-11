#include <cstring>

#include "EsMessage.h"


EsProtocol::Message::Message()
:m_MessageBuffer{}, // because char[] is first all field will be init to 0
m_isEscaped{false},
m_payLoadIsSet{false}
{
  m_MessageBuffer.m_Message.END_OF_FRAME = EsProtocol::END_OF_FRAME;

}

EsProtocol::Message::Message(const char* const message, size_t messageLenght, EsProtocol::Command command)
:m_MessageBuffer{}, // because char[] is first all field will be init to 0
m_isEscaped{false},
m_payLoadIsSet{false}
{
  m_MessageBuffer.m_Message.END_OF_FRAME = EsProtocol::END_OF_FRAME;
  m_MessageBuffer.m_Message.m_Header.command = command;
  if(messageLenght<= EsProtocol::nBytesDataSize)
  {
    // set payload temporary, might change due to escaping
    m_MessageBuffer.m_Message.m_Header.payLoadLenght = messageLenght;
    // copy data into message
    memcpy(m_MessageBuffer.m_Message.m_payload,message,messageLenght);
  }
  else
  {
    m_MessageBuffer.m_Message.m_Header.payLoadLenght = 0;
  }
  calcChecksum();
}

EsProtocol::Message::~Message()
{}

char* EsProtocol::Message::get()
{
  escapeEndOfFrameSections();
  calcPayloadLenght();
  m_MessageBuffer.m_Message.m_Checksum = calcChecksum();
  return m_MessageBuffer.m_Buffer;
}

char* EsProtocol::Message::getMemoryToWrite()
{
  return m_MessageBuffer.m_Buffer;
}

void EsProtocol::Message::setCommand(EsProtocol::Command theCommand)
{
  m_MessageBuffer.m_Message.m_Header.command = theCommand;
}

EsProtocol::Command& EsProtocol::Message::getCommand()
{
  return m_MessageBuffer.m_Message.m_Header.command;
}

EsProtocol::Header& EsProtocol::Message::getHeader()
{
  return m_MessageBuffer.m_Message.m_Header;
}

bool EsProtocol::Message::isValidEOF()
{
  if(m_MessageBuffer.m_Message.END_OF_FRAME == EsProtocol::END_OF_FRAME)
  {
    return true;
  }
  else
  {
    return false;
  }
}

uint32_t EsProtocol::Message::getChecksum()
{
  return m_MessageBuffer.m_Message.m_Checksum;
}

size_t EsProtocol::Message::calcChecksum()
{
  size_t tmpChecksum = 0;
  for(size_t position = 0; position < nBytesDataSize+sizeof(EsProtocol::Header); position++)
  {
    // simply add all byte values together
    tmpChecksum += m_MessageBuffer.m_Buffer[position];
  }
  return tmpChecksum;
}

char* EsProtocol::Message::getRawData()
{
  return m_MessageBuffer.m_Message.m_payload;
}

constexpr size_t EsProtocol::Message::getRawDataLength()
{
  return EsProtocol::nBytesDataSize;
}

void EsProtocol::Message::escapeEndOfFrameSections()
{
  for(size_t i = 0; i<EsProtocol::nBytesDataSize; i++)
  {
    // for better readability, should be equivalent to call sizeof() everytime
    constexpr size_t EOF_size = sizeof(EsProtocol::END_OF_FRAME);
    if(memcmp(&m_MessageBuffer.m_Message.m_payload[i], &EsProtocol::END_OF_FRAME, EOF_size) == 0
      && memcmp(&m_MessageBuffer.m_Message.m_payload[i+EOF_size], &EsProtocol::END_OF_FRAME, EOF_size) == 0)
    {
      // this sequence needs to be escaped
      memcpy( &m_MessageBuffer.m_Message.m_payload[i],
              &m_MessageBuffer.m_Message.m_payload[i+EOF_size],
              EsProtocol::nBytesDataSize-(i+EOF_size));
      i+=EOF_size;
    }
  }
}

void EsProtocol::Message::calcPayloadLenght()
{
  for(size_t end = EsProtocol::nBytesDataSize-1; end > 0; end--)
  {
    // going through the data, starting at the end
    // the position+1 of the first element which is not zero
    // is the payloadLenght.
    if(m_MessageBuffer.m_Message.m_payload[end] != 0)
    {
      m_MessageBuffer.m_Message.m_Header.payLoadLenght = end+1;
    }
  }
}
