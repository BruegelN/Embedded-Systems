#ifndef ES_MESSAGE_COMMAND_H
#define ES_MESSAGE_COMMAND_H

#include <cstdint>

/*
Known commands in V1.0:

0   | Invalid         | Invalides Kommando. Meldung auf Konsole
1   | Echo            | Die Daten werden vom Server 1:1 zurückgegeben.
2   | Echo Reply      | Vom Server geechote Daten.
3   | Shutdown        | Der Server beendet sich (sauber).
4   | Shutdown Reply  | Shutdown vom Server verstanden. Client beendet sich nun ebenfalls.
5+  | Unsupported     | Noch nicht implementiertes Kommando. Meldung auf Konsole mit Kommandonummer.
*/

namespace EsProtocol
{
  enum /*class*/ Command: uint16_t // TODO  because casting to int
  {
    Invalid = 0,
    Echo = 1,
    EchoReply = 2,
    Shutdown = 3,
    ShutdownReply = 4, // auf Nachfrage NICHT 3!
    Unsupported
  };
}

#endif //ES_MESSAGE_COMMAND_H
