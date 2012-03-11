#ifndef MEMORY_H
#define MEMORY_H

#include <new>
#include "Heap.h"

namespace CGE
{
    void* allocate(size_t inSize);
    void* allocate(size_t inSize, Heap& inHeap);
    void* reallocate(void* inMemory, size_t inSize, Heap& inHeap);
    void release(void* inMemory);
}

void* operator new(size_t inSize);
void operator delete(void* inData);

#endif
