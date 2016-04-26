#ifndef ES_MESSAGE_COMMAND_H
#define ES_MESSAGE_COMMAND_H

#include <cstdint>

namespace EsProtocol
{
  enum class Command: uint8_t
  {
    Invalid = 0,
    Echo = 1,
    EchoReply = 2,
    Shutdown = 3,
    ShutdownReply = 4,
    Unsupported
  };
}

#endif //ES_MESSAGE_COMMAND_H
