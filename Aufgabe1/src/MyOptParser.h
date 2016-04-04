#ifndef MY_OPT_PARSER_H
  #define MY_OPT_PARSER_H

#include "OptParser.h"

class MyOptParser final: public CmdLineOptParser {
  public:
    MyOptParser();

  protected:
    virtual bool option(char c, const char* info) override;
};


#endif /* MY_OPT_PARSER_H */
