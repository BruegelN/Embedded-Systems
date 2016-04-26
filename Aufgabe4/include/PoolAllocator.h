#ifndef POOL_ALLOCATOR_H
  #define POOL_ALLOCATOR_H

#include "IHeap.h"

template<size_t blockSize, size_t elements>
class PoolAllocator : IHeap {

public:
  // init data pool with zeros
  PoolAllocator():m_Pool{0}{};
  ~PoolAllocator();
  virtual void* Allocate(size_t size) override;
  virtual void Deallocate(void *) override;
  virtual size_t Available() const override;

private:
  // the given blocksize * elements is the poolsize in bytes.
  char m_Pool[blockSize*elements];

};

template<size_t blockSize, size_t elements>
void* PoolAllocator<blockSize, elements>::Allocate(size_t size)
{
  if(PoolAllocator::Available() < size)
  {
    
  }
  return m_Pool[size];
}

template<size_t blockSize, size_t elements>
void PoolAllocator<blockSize, elements>::Deallocate(void* position)
{
  position = nullptr;
}

template<size_t blockSize, size_t elements>
size_t PoolAllocator<blockSize, elements>::Available() const
{
  return sizeof(m_Pool);
}

#endif // POOL_ALLOCATOR_H
