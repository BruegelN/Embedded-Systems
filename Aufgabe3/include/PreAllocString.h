#ifndef PRE_ALLOC_STRING_H
  #define PRE_ALLOC_STRING_H

#include <cstdint> /* uint_32_t etc. */
#include <cstddef> /* size_t */
#include <cstdarg>
#include <cstring> /* strlen(), memcpy() */
#include "Printf.h"

/**
* String class which allocates a char[] with Buffersize+1 emlements at compile time.
* The extra byte is used to store the tailing '\0'.
* This allows the user to place Buffersize-emlemnts in string without caring about the zero termination
* or not enough space.
*/
template <size_t Buffersize>
class PreAllocString
{
  public:
    // init buffer with zero's
    PreAllocString():m_buffer{0}{}
    ~PreAllocString(){}

    // get raw data as const char*
    operator const char *() const;
    // get raw data as const void*
    operator const void *() const;
    // get elemtent with number idx of buffer as char
    // if out of range access the first element is returned!
    const char & operator [] (const int idx);

    // Current number of characters in string
     size_t GetLength() const;

    // Maximum number of characters possible
    size_t SizeOf() const;

    // clear the array
    void Empty();

    PreAllocString& operator =(       char        rhs);
    PreAllocString& operator =( const char*       rhs);
    PreAllocString& operator =(       char* const rhs);

    PreAllocString& operator +=(      char        rhs);
    PreAllocString& operator +=(      char const* rhs);
    void AddFormat ( const char* format, ... );
    void AddWhiteSpace ();

  private:
    // add extra char for tailing '\0'
    char m_buffer[Buffersize+1];

    size_t getFreeSpace();
    void appendToBuffer(char);
    void appendToBuffer(const char*);

};

/**
--------------------------------------------------------------------------------
                              IMPLEMENTTION
--------------------------------------------------------------------------------
*/

template <size_t Buffersize>
PreAllocString<Buffersize>::operator const char *() const
{
  return m_buffer;
}

template <size_t Buffersize>
PreAllocString<Buffersize>::operator const void *() const
{
  return static_cast<const void*>(m_buffer);
}
template <size_t Buffersize>
const char & PreAllocString<Buffersize>::operator [] (const int idx)
{
  if(static_cast<uint32_t>(idx) > Buffersize)
  {
    // in case it's negative the it will be casted to a very high positive number
    // or it's just large then the buffersize
    return m_buffer[0]; // undefined thus return first element
  }
  else
  {
    return m_buffer[idx];
  }
}

template <size_t Buffersize>
size_t PreAllocString<Buffersize>::GetLength() const
{
  return  strlen(m_buffer);
}

template <size_t Buffersize>
size_t PreAllocString<Buffersize>::SizeOf() const
{
  return  Buffersize;
}

template <size_t Buffersize>
void PreAllocString<Buffersize>::Empty()
{
  // because of the '\n'
  for( size_t i = 0; i < Buffersize+1; i++)
  {
    m_buffer[i] = 0;
  }
}

template <size_t Buffersize>
PreAllocString<Buffersize>& PreAllocString<Buffersize>::operator =( char rhs)
{
  // first clear old values
  this->Empty();
  m_buffer[0] = rhs;
  return *this;
}

template <size_t Buffersize>
PreAllocString<Buffersize>& PreAllocString<Buffersize>::operator =( const char* rhs)
{
  // first clear old values
  this->Empty();
  if(strlen(rhs) <= Buffersize)
  {
    // copy string
    memcpy(m_buffer, rhs, strlen(rhs));
    // else the string is to large
  }
  return *this;
}

template <size_t Buffersize>
PreAllocString<Buffersize>& PreAllocString<Buffersize>::operator =( char* const rhs)
{
  // first clear old values
  this->Empty();
  if(strlen(rhs) <= Buffersize)
  {
    // copy char
    memcpy(m_buffer, rhs, strlen(rhs));
    // else the char it to large
  }
  return *this;
}

template <size_t Buffersize>
PreAllocString<Buffersize>& PreAllocString<Buffersize>::operator +=(char rhs)
{
  if(this->getFreeSpace() >= sizeof(char))
  {
    // append it to current string
    this->appendToBuffer(rhs);
    // else not enought buffer space left!
  }
  return *this;
}

template <size_t Buffersize>
PreAllocString<Buffersize>& PreAllocString<Buffersize>::operator +=(char const* rhs)
{
  if(this->getFreeSpace() >= strlen(rhs))
  {
    // append it to current string
    this->appendToBuffer(rhs);
    // not enought buffer space left!
  }
  return *this;
}

template <size_t Buffersize>
void PreAllocString<Buffersize>::AddFormat(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  size_t endOfCurrentString = strlen(m_buffer);
  // The last element of m_buffer is \0 an thus it should not be overwritten by Printf!
  // Append it to the end of an possible existing string.
  Printf(&m_buffer[endOfCurrentString], (m_buffer+Buffersize-1), format, args);
  va_end(args);
}

template <size_t Buffersize>
void PreAllocString<Buffersize>::AddWhiteSpace ()
{
  size_t lenght = this->GetLength();
  if(lenght<this->SizeOf())
  {
    // at least one char free
    appendToBuffer(' ');
  }
}

template <size_t Buffersize>
size_t PreAllocString<Buffersize>::getFreeSpace()
{
  return Buffersize-strlen(m_buffer);
}

template <size_t Buffersize>
void PreAllocString<Buffersize>::appendToBuffer(char c)
{
  m_buffer[strlen(m_buffer) ] = c;
}

template <size_t Buffersize>
void PreAllocString<Buffersize>::appendToBuffer(const char* str)
{
  memcpy(&m_buffer[strlen(m_buffer) ], str, strlen(str));
}


#endif // PRE_ALLOC_STRING_H
