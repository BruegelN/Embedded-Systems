#ifndef SOCKET_OPT_PARSER_H
  #define SOCKET_OPT_PARSER_H

#include <cstdbool>
#include <cstdint>

#include "OptParser.h"


/*
CmdLine parser for UDP/Socket exercise in embedded systems lecture.

Options detected:
  -s is for socketmode
  -p is for the port number
  -i is for the ip-address
Either call it in server mode or provide an ip-address.
*/
class SocketOptParser final: public CmdLineOptParser {
  public:
    SocketOptParser();
    const char* getHelpText();
    bool isServerMode() const;
    uint16_t getPortNumber() const;
    const char* getIpAddrString() const;

  protected:
    virtual bool option(char c, const char* info) override;

  private:
    bool m_bServerMode;
    uint16_t m_u16PortNumber;
    const char* m_strIpAddress;

};


#endif // SOCKET_OPT_PARSER_H
