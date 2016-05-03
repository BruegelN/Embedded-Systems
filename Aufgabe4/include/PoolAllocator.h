#ifndef POOL_ALLOCATOR_H
  #define POOL_ALLOCATOR_H

#include <cstddef> // size_t

#include "IHeap.h"                // the interface
#include "ImplPoolAllocator.h"    // the actual implemantation


/*
* The real PoolAllocator.
* Allocates nElements of type T when created.
* To acces the storage for an element call Allocate(),
* which will return a void* to memory aread with sizeof(T).
* If less space is needed call Allocate(nBytes).
* If you don't need the memory anymore call Deallocate(ptrToElement).
* Via Available() you can check the number elements that can be allocated.
*/
template<typename T, size_t nElements = 2048>
class PoolAllocator : IHeap {

public:
  PoolAllocator():
  m_Pool{},          // set elements to default-initialize value e.g. int_t = 0
  m_ElementIsUsed{}  // At the beginning everything is free!
  {
    // NOTE:
    // This m_ElementIsFree{true} will only init the first element to true!
    // The rest of the array will be default-initialized
    // and because bool is of integral type, this is "reinterpret_cast<bool>0" -> false!
    // https://stackoverflow.com/questions/4059258/is-there-a-better-way-to-initialize-an-array
    // Make use of this "workaround" to not rewrite the memory in constructor again!

    static_assert(nElements > 0, "The nElements argument for PoolAllocator should be larger than 0.\n"
                                  "It defnies the number of elements with type T that can be stored.");

  };

  ~PoolAllocator()
  {
    // noting to do here
  };

  // PoolAllocator is sort of a central managing unit
  // thus it's neither a good idea to have a copy constructor
  // nor have a assign operator.
  PoolAllocator(const PoolAllocator& old) = delete;
  PoolAllocator& operator= (const PoolAllocator& rhs) = delete;

  // Allocates nBytes, nBytes(=size) has to be smaller or equal to sizeof(T)!
  // will return void* to address on success else will return nullptr
  virtual void* Allocate(size_t size = sizeof(T)) override
  {
    return ImplPoolAllocator::Allocate<T>( m_Pool,
                                          nElements,
                                          m_ElementIsUsed,
                                          size);
  }

  // Deallocates memory area staring with the given 'address'.
  // Afterwards this area is availible and can be allocated again.
  virtual void Deallocate(void * address) override
  {
    return ImplPoolAllocator::Deallocate<T>(m_Pool,
                                            nElements,
                                            m_ElementIsUsed,
                                            address);
  }
  // TODO someday/maybe virtual void Deallocate(T* address);

  // Returns the number of mElements that can be allocated.
  // There's no guarantee that the free mElements are placed in a row.
  virtual size_t Available() const override
  {
    return ImplPoolAllocator::Available<T>(m_Pool,
                                          nElements,
                                          m_ElementIsUsed);
  }

private:
  // nElements of type T which can be used be others.
  T m_Pool[nElements];
  // for every element we have to take note if it's allocated, thus not free to use, or not.
  bool m_ElementIsUsed[nElements];

};


#endif // POOL_ALLOCATOR_H
