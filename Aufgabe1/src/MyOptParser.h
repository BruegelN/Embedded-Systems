#ifndef MY_OPT_PARSER_H
  #define MY_OPT_PARSER_H

#include "OptParser.h"

class MyOptParser : public CmdLineOptParser {
  public:
    MyOptParser();

  protected:
    virtual bool option(char c, const char* info);
};


#endif /* MY_OPT_PARSER_H */
