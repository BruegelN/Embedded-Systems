#ifndef MEMORY_CONTROL_STRUCT_H
#define MEMORY_CONTROL_STRUCT_H

#include <cstdbool>

struct MemoryCtrlStruct
{
  // TODO really "usefull" if only 2bit used?
  bool isFree;              // : 1;
  bool isEndOfMemoryBlock;  //: 1;
};

#endif // MEMORY_CONTROL_STRUCT_H
