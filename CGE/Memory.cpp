#include "Memory.h"
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iostream>

namespace CGE
{
    static Heap GeneralHeap("General");
    static const unsigned int Canary = 0xdeadbeef;

    struct Header
    {
        Heap* heap;
        Header* next;
        Header* previous;
        size_t size;
        unsigned int canary;
    };

    static Header* gFirstHeader = NULL;

    void* allocate(size_t inSize, Heap& inHeap)
    {
        size_t total = sizeof(Header) + inSize;
        char* memory = (char*)malloc(total);
        char* outBlock = NULL;

        if (memory)
        {
            inHeap.allocate(inSize);

            Header* header = (Header*)memory;
            memset(header, 0, sizeof(Header));
            header->heap = &inHeap;
            header->size = inSize;
            header->canary = Canary;

            if (gFirstHeader)
            {
                assert(gFirstHeader->previous == NULL);
                gFirstHeader->previous = header;
                header->next = gFirstHeader;
            }

            gFirstHeader = header;
            outBlock = memory + sizeof(Header);
        }

        return outBlock;
    }

    void* reallocate(void* inMemory, size_t inSize, Heap& inHeap)
    {
        assert(inSize > 0);

        void* outBlock = inMemory;

        if (inMemory)
        {
            char* block = (char*)inMemory;
            block -= sizeof(Header);
            Header* header = (Header*)block;
            assert(header->canary == Canary);

            if (header->size < inSize)
            {
                outBlock = allocate(inSize, inHeap);
                memcpy(outBlock, inMemory, header->size);
                release(inMemory);
            }
        }
        else
        {
            outBlock = allocate(inSize, inHeap);
        }

        return outBlock;
    }

    void release(void* inMemory)
    {
        if (inMemory)
        {
            char* block = (char*)inMemory;
            block -= sizeof(Header);
            Header* header = (Header*)block;
            assert(header->canary == Canary);

            header->heap->release(header->size);

            if (gFirstHeader == header) gFirstHeader = gFirstHeader->next;

            if (header->next) header->next->previous = header->previous;
            if (header->previous) header->previous->next = header->next;

            free(block);
        }
    }
}

void* operator new(size_t inSize)
{
    return CGE::allocate(inSize, CGE::GeneralHeap);
}

void operator delete(void* inData)
{
    CGE::release(inData);
}
