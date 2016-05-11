#ifndef ES_MESSAGE_H
#define ES_MESSAGE_H

#include <cstdint>
#include <cstddef>

#include "EsMessageHeader.h"
#include "EsMessageCommand.h"

/*
An EsProtocol::Message starts with a EsProtocol::Header and the actual data.
When

0                    63         n              n+32          n+64
+--------------------+----------+--------------+--------------+
| EsProtocol::Header | data ... |   Checksum   | END_OF_FRAME |
+--------------------+----------+--------------+--------------+

TODO framing
end of frame (and start of frame) mit festem Pattern
ggf escaping falls dieses bit-muster in daten (oder im header) vorkommmt erneut anhängen

*/
namespace EsProtocol
{
  constexpr uint32_t END_OF_FRAME = 0xA9A; // aka 0000 1010 1001 1010
  // max payload [bytes]
  // Just to specify a limit however you could adjust the UDP socket rcvbuf
  // via setsockopt()!
  constexpr size_t nBytesDataSize = 1024;

  /*
  * The Message which sould be transfered.
  * Some additional infromation are added.
  * NOTE: by now hton*() and nton*() is NOT used.
  *       Thus you might ran into some issues when running it elsewhere
  *       than on localhost!.
  */
  class Message
  {
    // the pure message, internal only
    struct RawMessage
    {
      EsProtocol::Header m_Header;
      char m_payload[EsProtocol::nBytesDataSize];
      uint32_t m_Checksum;
      uint32_t END_OF_FRAME;
    }__attribute__ ((__packed__));

  public:
    Message();
    Message(const char* const message, size_t messageLenght, EsProtocol::Command);
    ~Message();
    // return pointer to underlaying buffer, e.g. for sending
    char* get();
    char* getMemoryToWrite();
    void setCommand(EsProtocol::Command);
    EsProtocol::Command& getCommand();
    EsProtocol::Header& getHeader();
    bool isValidEOF();
    uint32_t getChecksum();
    size_t calcChecksum();
    char* getRawData();
    constexpr static size_t getRawDataLength();
    // size of a full frame, e.g. when reading form network
    constexpr static size_t size()
    {
      return sizeof(EsProtocol::Message::RawMessage);
    }
    // don't use this one
    Message(const Message& old) = delete;
    Message& operator= (const Message& rhs);
  private:
    // a unoin with the message and a raw buffer for easy handling.
    union MessageBuffer
    {
      char m_Buffer[sizeof(EsProtocol::Message::RawMessage)];
      EsProtocol::Message::RawMessage m_Message;
    };
    MessageBuffer m_MessageBuffer;
    bool m_isEscaped;
    bool m_payLoadIsSet;

    void calcPayloadLenght();
    void escapeEndOfFrameSections();
  };
}


#endif // ES_MESSAGE_H
