#include <iostream> /* std::cout */
#include <cstring> /* strncmp */

#include "OptParser.h"


CmdLineOptParser::CmdLineOptParser()
{
}

bool CmdLineOptParser::parse(int argc, const char **argv)
{
  /* when ever it's not possible to parse the arguments this will be set to false */
  bool tmpReturn = true;

  if((2 <= argc) && argv != nullptr)
  {
    /* Skip over program name */
    argc--, argv++;

    for(int i=0; i<argc; i++)
    {
      if( '-' == argv[i][0] && (0 != argv[i][1]))
      {
        /* found a new key(-c) thus argv[i][1] is the key(char c).*/
        if((0 != argv[i][2]) && '=' == argv[i][2])
        {
          /* it's an asingment and with argv[i][3] the value(info starts) */
          if(this->option(argv[i][1] , &argv[i][3]) == false)
          {
            tmpReturn = false;
          }
        }
        else if(0 < argv[i][2])
        {
          /* value start right after key */
          if(this->option(argv[i][1] , &argv[i][2]) == false)
          {
            tmpReturn = false;
          }
        }
        else
        {
          /**
          * Only -x option given.
          * So either -x key
          * or -x -x is possible.
          * But first check if there is a next argument given!
          */
          if((i+1) < argc)
          {
            if('-' == argv[i+1][0])
            {
              /**
              * The first char of the next argument block is another dash.
              * Which means we're done, because it's the next key and there is no
              * value(info is nullptr).
              */
              if(this->option(argv[i][1] , nullptr) == false)
              {
                tmpReturn = false;
              }
            }
            else
            {
              /**
              * A next argument exist and it's not a new key (-x).
              * The next argument is the value(info) for the given key.
              */
              if(this->option(argv[i][1] , &argv[i+1][0]) == false)
              {
                tmpReturn = false;
              }

              /**
              * Don't forget to go over the next argument.
              * Even if we check every argument if it starts with '-'.
              */
              ++i;
            }
          }
          else
          {
            /**
            * The given -x ist the last argument
            * which means there is no value(info is nullptr).
           */
            if(this->option(argv[i][1] , nullptr) == false)
            {
              tmpReturn = false;
            }
          }
        }
      }
      else
      {
        /* either there is no dash or the field after the dash is empty/equal to zero */
        tmpReturn = false;
      }
    }
  }
  else
  {
    /* no arguments given */
    tmpReturn = false;
  }

  /* if one or more errors occured this will be false */
  return tmpReturn;
}

bool CmdLineOptParser::option(char c, const char *info)
{
  std::cout << "\tArgument: " << c << " given." << std::endl;
  if(nullptr != info)
  {
    std::cout << "\tValue: " << std::string(info) << std::endl;
  }
  else
  {
    std::cout << "\tNo value given." << std::endl;
  }
  return true;
}
