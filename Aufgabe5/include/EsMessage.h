#ifndef ES_MESSAGE_H
#define ES_MESSAGE_H

#include <cstdint>
#include "EsMessageHeader.h"
#include "EsMessageCommand.h"

namespace EsProtocol
{
  class Message
  {
  public:
    Message();
    ~Message();
  private:
    EsProtocol::Header m_Header;
  };
}


#endif // ES_MESSAGE_H
