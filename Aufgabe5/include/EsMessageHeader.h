#ifndef ES_MESSAGE_HEADER_H
#define ES_MESSAGE_HEADER_H

#include "EsMessageCommand.h"

/*
The struct for a header of a EsProtocol::Message.
0               15               31                47               63
+----------------+----------------+----------------+----------------+----------+
| payloadLength  | sequenceNumber | command        | handle         | data ... |
+----------------+----------------+----------------+----------------+----------+
payloadLength: Overall number of bytes of whole EsProtocol::Message.
sequenceNumber: The number of the message transfered, should increment everytime.
command: A known EsProtocol::Command.
handle: TODO Antwort zu einer Nachricht zuzuordnen, für bestätigung.
data: The acutel payload
*/

namespace EsProtocol
{
  struct Header
  {
    uint16_t payLoadLenght : 16;
    uint16_t sequenceNumber : 16;
    EsProtocol::Command command : 16; // TODO check if this really works
    uint16_t handle : 16;
  }__attribute__ ((__packed__));
}

#endif //ES_MESSAGE_HEADER_H
