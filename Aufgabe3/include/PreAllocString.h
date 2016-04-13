#ifndef PRE_ALLOC_STRING_H
  #define PRE_ALLOC_STRING_H

#include <cstdint> /* uint_32_t etc. */
#include <cstddef> /* size_t */
#include <cstdio>
#include <cstdarg>
#include <cstring> /* strlen(), memcpy() */

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
    const char & operator [] (const int idx);

    // Current number of characters in string
     size_t GetLength() const;

    // TODO constexpr allowed?
    // Maximum number of characters possible
    constexpr size_t SizeOf() const;

    // clear the array
    void Empty();

    PreAllocString& operator =(       char        rhs);
    PreAllocString& operator =( const char*       rhs);
    PreAllocString& operator =(       char* const rhs);

    PreAllocString& operator +=(      char        rhs);
    PreAllocString& operator +=(const char*       rhs);
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
  return m_buffer[idx];
}

template <size_t Buffersize>
size_t PreAllocString<Buffersize>::GetLength() const
{
  return  strlen(m_buffer);
}

template <size_t Buffersize>
constexpr size_t PreAllocString<Buffersize>::SizeOf() const
{
  return  Buffersize;
}

template <size_t Buffersize>
void PreAllocString<Buffersize>::Empty()
{
  for( size_t i = 0; i < Buffersize; i++)
  {
    m_buffer[i] = 0;
  }
}

template <size_t Buffersize>
void PreAllocString<Buffersize>::AddFormat(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  size_t lenght = this->GetLength();
  if(lenght<this->SizeOf())
  {
    // TODO while args
    //snprintf(m_buffer, Buffersize, format, ...);

  }
  va_end(args);
}

template <size_t Buffersize>
void PreAllocString<Buffersize>::AddWhiteSpace ()
{
  size_t lenght = this->GetLength();
  if(lenght<this->SizeOf())
  {
    // at least one char free
    m_buffer[lenght+1] = ' ';
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
  m_buffer[strlen(m_buffer) +1 ] = c;
}

template <size_t Buffersize>
void PreAllocString<Buffersize>::appendToBuffer(const char* str)
{
  memcpy(&m_buffer[strlen(m_buffer) +1 ], str, strlen(str));
}


#endif // PRE_ALLOC_STRING_H
