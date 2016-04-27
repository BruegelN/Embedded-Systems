#ifndef ES_MESSAGE_HEADER_H
#define ES_MESSAGE_HEADER_H

#include "EsMessageCommand.h"

namespace EsProtocol
{
  struct Header
  {
    uint16_t payLoadLenght : 16;
    uint16_t sequenceNumber : 16;
    EsProtocol::Command command : 8; // TODO check if this really works
    uint8_t handle : 8;
  };
}

#endif //ES_MESSAGE_HEADER_H
