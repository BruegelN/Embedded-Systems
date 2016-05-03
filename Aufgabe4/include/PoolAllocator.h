#ifndef POOL_ALLOCATOR_H
  #define POOL_ALLOCATOR_H

#include <cstddef> // size_t

#include "IHeap.h"            // the interface
#include "MemoryCtrlStruct.h" // to mark a piece memory as END and/or END
#include "MemoryHandler.h"    // the implemantation


/*
* PoolAllocator
*/

template<size_t blockSize, size_t nElements>
// TODO: template<typename T, size_t nElements>
// with array of type T and make use of sizeof(t)
class PoolAllocator : IHeap {

public:
  // init data pool with zeros
  PoolAllocator(): m_Pool{0}
  {
    static_assert(blockSize != 0, "BlockSize of PoolAllocator has to be >0");
    static_assert(nElements != 0, "nElements of PoolAllocator should be larger than 0");
    // I don't know if this can be done by initializer lists!
    for(size_t i = 0; i < nElements; i++)
    {
      // Every element is free and not an end.
      m_PoolManager[i].isFree = true;
      m_PoolManager[i].isEndOfMemoryBlock = false;
    }
    // the last element is allways the end!
    m_PoolManager[nElements-1].isEndOfMemoryBlock = true;
  };

  ~PoolAllocator()
  {
    // noting to do here
  };

  // Allocates nBytes/size
  // will return void* to address on success else will return nullptr
  virtual void* Allocate(size_t size) override
  {
    return MemoryHandler::Allocate(size, m_Pool, blockSize, nElements, m_PoolManager);
  };


  // Deallocates memory area staring with the given 'address'.
  // Afterwards this area is availible and reusable.
  virtual void Deallocate(void * address) override
  {
    return MemoryHandler::Deallocate(address,m_Pool, blockSize, nElements, m_PoolManager);
  };

  /* Returns the larges available space to allocate in bytes.
  * NOTE: Overall available size would propably confuse the user
  *  if he/she wants to allocate all availible space at once!
  */
  virtual size_t Available() const override
  {
    return MemoryHandler::Available(blockSize, nElements, m_PoolManager);
  };

private:
  // the given blocksize * nElements is the poolsize in bytes.
  char m_Pool[blockSize*nElements];
  // for every element there is MemoryCtrlStruct to tell if this element isFree
  // is isEndOfMemoryBlock.
  MemoryCtrlStruct m_PoolManager[nElements];

};
#endif // POOL_ALLOCATOR_H
