#include <iostream>

#include "PoolAllocator.h"

int main(void)
{

  std::cout << "Test with PoolAllocator<uint64_t,8>" << std::endl;
    PoolAllocator<uint64_t,8> intPool;

    std::cout << intPool.Available() << " elements free" << std::endl;

    // smaller
    void* intTest1 = intPool.Allocate(sizeof(uint8_t));
    std::cout << "intTest1: " << intTest1 << std::endl;
    std::cout << intPool.Available() <<" elements free" << std::endl;

    // max
    uint8_t* intTest2 = reinterpret_cast<uint8_t*>(intPool.Allocate(sizeof(uint64_t)));
    std::cout << "intTest2: " << static_cast<void*>(intTest2) << std::endl;
    std::cout << "&intTest2[1] " << static_cast<void*>(&intTest2[1]) << std::endl;
    std::cout << intPool.Available() <<" elements free" << std::endl;

    // to large
    void* intTest3 = intPool.Allocate(4*sizeof(uint64_t));
    std::cout << "intTest3: " << intTest3 << std::endl;
    std::cout << intPool.Available() <<" elements free" << std::endl;

    intPool.Deallocate(intTest1);
    std::cout << "after first deallocation "<< intPool.Available() <<" elements free" << std::endl;
    void* intTest4 = intPool.Allocate(sizeof(int));
    std::cout << "intTest4: " << intTest4 << " should be same as intTest1" << std::endl;
    std::cout << intPool.Available() <<" elements free" << std::endl;

    /* try to free address in middle of memory block, should work */
    intPool.Deallocate(static_cast<void*>(&intTest2[1]));
    std::cout << intPool.Available() <<" elements free" << std::endl;

    intPool.Deallocate(intTest4);
    std::cout << intPool.Available() <<" elements free" << std::endl;





    std::cout << std::endl << std::endl;
    std::cout << "Test with PoolAllocator<std::string,8>" << std::endl;

    PoolAllocator<std::string,8> stringPool;

    std::cout << stringPool.Available() << " elements free" << std::endl;

    void* stringTest1 = stringPool.Allocate(sizeof(uint8_t));    // small enough
    std::cout << "stringTest1: " << stringTest1 << std::endl;
    std::cout << stringPool.Available() <<" elements free" << std::endl;

    void* stringTest2 = stringPool.Allocate(sizeof(int));        // max
    std::cout << "stringTest2: " << stringTest2 << std::endl;
    std::cout << stringPool.Available() <<" elements free" << std::endl;

    void* stringTest3 = stringPool.Allocate(4*sizeof(uint64_t)); // to large
    std::cout << "stringTest3: " << stringTest3 << std::endl;
    std::cout << stringPool.Available() <<" elements free" << std::endl;

    stringPool.Deallocate(stringTest1);
    std::cout << "after first deallocation "<< stringPool.Available() <<" elements free" << std::endl;
    void* stringTest4 = stringPool.Allocate(sizeof(int));
    std::cout << "stringTest4: " << stringTest4 << " should be same as stringTest1" << std::endl;
    std::cout << stringPool.Available() <<" elements free" << std::endl;

    stringPool.Deallocate(stringTest2);
    std::cout << stringPool.Available() <<" elements free" << std::endl;

    stringPool.Deallocate(stringTest4);
    std::cout << stringPool.Available() <<" elements free" << std::endl;

    /*
    This doesn't work on purpos!
    PoolAllocator<int,2> pool1;
    PoolAllocator<int,2> pool2;
    PoolAllocator<int,2> pool3 = pool2;
    pool2 = pool1;
    */
    return 0;

}
