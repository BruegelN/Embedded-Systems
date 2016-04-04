#ifndef OPT_PARSER_H
  #define OPT_PARSER_H


class CmdLineOptParser {
  public:
    CmdLineOptParser();

    /**
    * Parses the given command-line arguements.
    * param[in] int argc: number of arguments
    * param[in] char** argv: array of char pointers to the arguments
    *
    * return: true if successfully parsed all args,
    *         false if one or more error happend.
    */
    bool parse(int argc, const char** argv);
    // Alternative to prevent childen to override this function:
    // virtual bool parse(int argc, const char** argv) final;

  protected:
    virtual bool option(char c, const char* info);
};


#endif /* OPT_PARSER_H */
