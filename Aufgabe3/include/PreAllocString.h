#ifndef PRE_ALLOC_STRING_H
  #define PRE_ALLOC_STRING_H

#include <cstdint> /* uint_32_t etc. */
#include <cstddef> /* size_t */

template <size_t Buffersize>
class PreAllocString
{
  public:
    // init buffer with zero's
    PreAllocString():m_buffer{0}{}
    ~PreAllocString(){}

    operator const char *() const
    {
      return m_buffer;
    }

    operator const void *() const
    {
      return static_cast<const void*>(m_buffer);
    }

    const char & operator [] (const int idx)
    {
      return m_buffer[idx];
    }

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

    PreAllocString& operator +=(char              rhs);
    PreAllocString& operator +=(char      const*  rhs);
    void AddFormat ( const char* format, ... );
    void AddWhiteSpace ();

  private:
    char m_buffer[Buffersize];

};

/**
--------------------------------------------------------------------------------
                              IMPLEMENTTION
--------------------------------------------------------------------------------
*/

template <size_t Buffersize>
size_t PreAllocString<Buffersize>::GetLength() const
{
  /* TODO return real string lenght */
  return  strlen(m_buffer);
}

template <size_t Buffersize>
constexpr size_t PreAllocString<Buffersize>::SizeOf() const
{
  return  Buffersize-1;
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
void PreAllocString<Buffersize>::AddWhiteSpace ()
{
  if(true)
  {

  }
}



#endif // PRE_ALLOC_STRING_H
