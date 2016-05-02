#ifndef IHEAP_H
  #define IHEAP_H

#include <cstddef> // size_t

/*
* Interface for PoolAllocator
*/

class IHeap {
public:
   virtual void* Allocate(size_t size) = 0;
   virtual void Deallocate(void *) = 0;
   virtual size_t Available () const = 0;
};

#endif // IHEAP_H
