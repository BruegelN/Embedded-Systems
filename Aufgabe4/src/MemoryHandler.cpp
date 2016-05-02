#include "MemoryHandler.h"


void* MemoryHandler::Allocate(const size_t &nBytes, char* const pool,
                              const size_t &blockSize, const size_t &nElements,
                              MemoryCtrlStruct* const poolManager)
{
  if( pool ==  nullptr
    || poolManager == nullptr
    || nBytes ==  0
    || blockSize ==  0
    || nElements ==  0
    )
  {
    return nullptr;// invalid call!
  }

  size_t currentFreeMemBlock = 0;
  for(size_t position = 0; position < nElements; position++)
  {
    if(poolManager[position].isFree)
    {
      // increment counter for free memory block
      currentFreeMemBlock++;
    }
    else // it's a piece memory used by someone else
    {
      // however the old position might have been free and large enough
      if(currentFreeMemBlock*blockSize >= nBytes)
      {
        // the area we looked at before has been large enough
        size_t lastFreePosition = position - 1;
        size_t posToMark;
        for( posToMark = lastFreePosition - currentFreeMemBlock;
            posToMark*blockSize < nBytes; // only mark the needed area even if there is more!
            posToMark++)
        {

          poolManager[posToMark].isFree = false;
          poolManager[posToMark].isEndOfMemoryBlock = false;
        }
        // the last element is an end of a memory block
        poolManager[posToMark].isEndOfMemoryBlock = true;
        // the n'th elements raw address is it's position * blockSize
        return static_cast<void*>( &pool[lastFreePosition*blockSize] );
      }
      // else haven't found a large enough area thus reset tmp counter
      currentFreeMemBlock = 0;
    }
  }

  // if we reach this position there isn't a free piece of memory of nBytes size!
  return nullptr;
}

void MemoryHandler::Deallocate( const void* const address, const char* const pool,
                                const size_t &blockSize, const size_t &nElements,
                                MemoryCtrlStruct* const poolManager)
{
  if( address == nullptr
      || pool ==  nullptr
      || poolManager == nullptr
      || address < &pool[0] // address is placed in memory befor pool!
      || address > &pool[blockSize*nElements] // address is placed in memory behind pool!
      || blockSize == 0
      || nElements == 0
    )
  {
    return;// invalid call! returntype bool ?!
  }

  // search position of given address not the best runtime for very large pool's
  size_t pos;
  for(pos = 0; &pool[pos*blockSize] != address; pos++)
  {
    // noting to do here, jump over not needed areas
  }

  do
  {
    poolManager[pos].isFree = true;
  }while(poolManager[pos].isEndOfMemoryBlock);
}

size_t MemoryHandler::Available(const size_t &blockSize, const size_t &nElements,
                                const MemoryCtrlStruct* const poolManager)
{
  if (poolManager == nullptr
      || blockSize == 0
      || nElements == 0
      )
  {
    return 0; // invalid call
  }

  size_t currentFreeMemBlock = 0, largestFreeMemBlock = 0;
  for(size_t position = 0; position < nElements; position++)
  {
    if(poolManager[position].isFree)
    {
      // increment counter for free memory block
      currentFreeMemBlock++;
    }
    else if(currentFreeMemBlock > largestFreeMemBlock)
    {
      largestFreeMemBlock = currentFreeMemBlock;
      currentFreeMemBlock = 0;
    }
  }

  // nBlocks where each has a sizeof() = blockSize will give nBytes
  return largestFreeMemBlock*blockSize;
}

size_t MemoryHandler::Available(const size_t &nElements,
                                const MemoryCtrlStruct* const poolManager)
{
  if (poolManager == nullptr
      || nElements == 0
      )
  {
    return 0; // invalid call
  }

  size_t currentFreeMemBlock = 0, largestFreeMemBlock = 0;
  for(size_t position = 0; position < nElements; position++)
  {
    if(poolManager[position].isFree)
    {
      // increment counter for free memory block
      currentFreeMemBlock++;
    }
    else if(currentFreeMemBlock > largestFreeMemBlock)
    {
      largestFreeMemBlock = currentFreeMemBlock;
      currentFreeMemBlock = 0;
    }
  }

  return largestFreeMemBlock;
}
