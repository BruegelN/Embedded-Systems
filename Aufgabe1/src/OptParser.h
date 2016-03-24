#ifndef OPT_PARSER_H
  #define OPT_PARSER_H


class CmdLineOptParser {
  public:
    CmdLineOptParser();

    bool parse(int argc, const char** argv);
  protected:
    virtual bool option(char c, const char* info);
};


#endif /* OPT_PARSER_H */
