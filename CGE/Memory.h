#ifndef MEMORY_H
#define MEMORY_H

#include <new>

namespace CGE
{
    void memoryDump();
}

void* operator new(size_t inSize);
void operator delete(void* inData);

#endif
