#ifndef LEGACY_MEMORY_HANDLER_H
#define LEGACY_MEMORY_HANDLER_H

#include <cstddef> // size_t

#include "Legacy_MemoryCtrlStruct.h"

namespace legacy
{
/*
* Implementation for PoolAllocater.
*/
class MemoryHandler
{
public:
  /*
  * Try's to allocates 'nBytes' of ’pool' with 'blockSize'.
  * 'poolManager' is used to check the elements in 'pool'.
  * if possible return the start address and set the flags in 'poolManager'.
  * else nullptr.
  */
  static void* Allocate( const size_t &nBytes, char* const pool,
                                const size_t &blockSize, const size_t &nElements,
                                MemoryCtrlStruct* const poolManager);

  /*
  * Marks the memory area starting with 'address' unitl next isEndOfMemoryBlock as isFree.
  */
  static void Deallocate(  const void* const address, const char* const pool,
                                  const size_t &blockSize, const size_t &nElements,
                                  MemoryCtrlStruct* const poolManager);

  /*
  * Searches largest free memory area of a memory pool managed by poolManager,
  * this pool can contains 'nElements' of 'blockSize'.
  * Will return largest number of 'nBytes' which are FREE.
  * NOTE: The overall free memory is NOT returned on purpos.
  * So it's guaranteed that a user can Allocate the amound returned.
  */
  static size_t Available( const size_t &blockSize, const size_t &nElements,
                                  const MemoryCtrlStruct* const poolManager);





  // TODO: the following version of might be confusing
  /*
  * Searches largest free memory area of a memory pool managed by poolManager,
  * This pool can contains 'nElements' of a certain size.
  * Will return the largest number of elements that can be stored at once.
  * NOTE: The overall free memory is NOT returned on purpos.
  * So it's guaranteed that a user can Allocate the amound returned.
  */
  inline static size_t Available( const size_t &nElements,
                                  const MemoryCtrlStruct* const poolManager);

private:
  // Creating an instance of MemoryHandler is not very usefull!
  MemoryHandler();
  ~MemoryHandler();
};

} // namespace legacy

#endif // MEMORY_HANDLER_H
