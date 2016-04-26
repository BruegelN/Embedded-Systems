#ifndef SOCKET_OPT_PARSER_H
  #define SOCKET_OPT_PARSER_H

#include <cstdbool>
#include <cstdint>

#include "OptParser.h"

class SocketOptParser final: public CmdLineOptParser {
  public:
    SocketOptParser();
    const char* getHelpText();
    bool isServerMode() const;
    uint32_t getPortNumber() const;
    const char* getIpAddrString() const;

  protected:
    virtual bool option(char c, const char* info) override;

  private:
    bool m_bServerMode;
    uint32_t m_u32PortNumber;
    const char* m_strIpAddress;

};


#endif // SOCKET_OPT_PARSER_H
