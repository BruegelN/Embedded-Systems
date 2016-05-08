#ifndef ES_MESSAGE_H
#define ES_MESSAGE_H

#include <cstdint>
#include <cstddef>

#include "EsMessageHeader.h"
#include "EsMessageCommand.h"

/*
An EsProtocol::Message starts with a EsProtocol::Header and the actual data.
When

0                    63         n       n+16          n+16+?
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
    // max number of raw data [bytes]
    const static size_t nBytesDataSize = 1024;
    EsProtocol::Command getCommand();
    char* getRawData();
    size_t getRawDataLength();
  private:
    EsProtocol::Header m_Header;
    size_t calcPayloadLenght(char* p_Data);
    char m_rawData[nBytesDataSize];
  };
}


#endif // ES_MESSAGE_H
