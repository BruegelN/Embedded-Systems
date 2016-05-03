#ifndef MEMORY_CONTROL_STRUCT_H
#define MEMORY_CONTROL_STRUCT_H

namespace legacy
{

struct MemoryCtrlStruct
{
  // TODO really "usefull" if only 2bit used?
  bool isFree;              // : 1;
  bool isEndOfMemoryBlock;  //: 1;
};

} // namespace legacy

#endif // MEMORY_CONTROL_STRUCT_H
