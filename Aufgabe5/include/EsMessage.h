#ifndef ES_MESSAGE_H
#define ES_MESSAGE_H

#include <cstdint>

#include "EsMessageHeader.h"
#include "EsMessageCommand.h"

/*
An EsProtocol::Message starts with a EsProtocol::Header and the actual data.
When

0                    63
+--------------------+----------+-------+--------------+
| EsProtocol::Header | data ... |  CRC  | END_OF_FRAME |
+--------------------+----------+-------+--------------+

TODO framing
end of frame (and start of frame) mit festem Pattern
ggf escaping falls dieses bit-muster in daten (oder im header) vorkommmt erneut anhängen

*/
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
