#ifndef IMPL_POOL_ALLOCATOR_H
#define IMPL_POOL_ALLOCATOR_H

#include <cstddef> // size_t

// Use a namespace instead of a class.
// because it's just a collection of static methods
// and creating an instance ImplPoolAllocator doesn't make sense, too.
// NOTE:
// Use templatated methods only for the type of elements.
// The element count of PoolAllocator is templated, too.
// For PoolAllocator<int,10> and PoolAllocator<int,20> only the needed
// ImplPoolAllocator::Allocate<int> is created, once for every used type.
namespace ImplPoolAllocator
{

  /*
  * Searches the first 'memoryPool'-element of type T
  * that is marked as free in 'elementIsUsed'-bool[nElements]
  * then returns it's address and mark elementIsUsed[#(element)]=false.
  * If called with wrong parametes or no space availible nullptr is returned!
  */
  template<typename T>
  void* Allocate( T* const memoryPool,
                  const size_t nElements,
                  bool* const elementIsUsed,
                  const size_t nBytes)
  {
    if( memoryPool == nullptr
        || nElements == 0
        || elementIsUsed == 0
        || nBytes == 0
        || nBytes > sizeof(T)) // too large
    {
      // invalid call
      return nullptr;
    }

    for(size_t i = 0; i < nElements; i++)
    {
      if(!elementIsUsed[i])
      {
        elementIsUsed[i] = true;
        // return the first free element
        return static_cast<void*>(&memoryPool[i]);
      }
    }

    // haven't found an element which is marked as free
    return nullptr;
  }

  /*
  * Marks an element as free if address is pointer to an element
  * or in the area of an element.
  *  ----+--------+--
  *   ...| element| ..
  *  ----+--------+--
  *      ^address^has to be in range [&element,&element+1[
  */
  template<typename T>
  void Deallocate(const T* const memoryPool,
                  const size_t nElements,
                  bool* const elementIsUsed,
                  const void* const address)
  {
    if( memoryPool == nullptr
        || nElements == 0
        || elementIsUsed == 0
        || address == nullptr
        || address < memoryPool // out of range!
        || address > &memoryPool[nElements])
    {
      // invalid call
      return;
    }

    for(size_t i = 0; i < nElements; i++)
    {
      if(address >= &memoryPool[i] && address < &memoryPool[i+1])
      {
        // if address is found mark this element as free and return
        elementIsUsed[i] = false;
        return;
      }
    }

  };


  /*
  * A 'memoryPool' of type T with 'nElements' and bool elementIsUsed[nElements].
  * Returns number of elements with elementIsUsed[#(element)]=true.
  *
  */
  template<typename T>
  size_t Available( const T* const memoryPool,
                    const size_t nElements,
                    const bool* const elementIsUsed)
  {
    if( memoryPool == nullptr
        || nElements == 0
        || elementIsUsed == 0)
    {
      // invalid call
      return 0;
    }
    size_t freeElementCount = 0;
    // increment counter for every free element in pool
    for(size_t i = 0; i < nElements; i++)
    {
      if(!elementIsUsed[i])
      {
        freeElementCount++;
      }
    }
    return freeElementCount;
  }


} // namespace ImplPoolAllocator

#endif // IMPL_POOL_ALLOCATOR_H
