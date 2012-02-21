#include "Memory.h"
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iostream>

namespace CGE
{
    struct Header
    {
        Header* next;
        Header* previous;
        size_t size;
        unsigned int canary;
    };

    static Header* gFirstHeader = NULL;
    static size_t gNumAllocations = 0;
    static size_t gNumReleases = 0;
    static const unsigned int Canary = 0xdeadbeef;

    static void* allocate(size_t inSize)
    {
        size_t total = sizeof(Header) + inSize;
        char* memory = (char*)malloc(total);

        Header* header = (Header*)memory;
        memset(header, 0, sizeof(Header));
        header->size = inSize;
        header->canary = Canary;

        if (gFirstHeader)
        {
            assert(gFirstHeader->previous == NULL);
            gFirstHeader->previous = header;
            header->next = gFirstHeader;
        }

        gFirstHeader = header;

        return memory + sizeof(Header);
    }

    static void release(void* inMemory)
    {
        if (inMemory)
        {
            char* block = (char*)inMemory;
            block -= sizeof(Header);
            Header* header = (Header*)block;
            assert(header->canary == Canary);

            if (gFirstHeader == header) gFirstHeader = gFirstHeader->next;

            if (header->next) header->next->previous = header->previous;
            if (header->previous) header->previous->next = header->next;

            free(block);
        }
    }

    void memoryDump()
    {
        size_t total = 0;
        size_t count = 0;
        for (Header* h = gFirstHeader; h; h = h->next)
        {
            total += h->size;
            ++count;
        }

        std::cout << count << " blocks active : " << total
            << " bytes allocated\n" << gNumAllocations << " allocations and "
            << gNumReleases << " releases\n";
    }
}

void* operator new(size_t inSize)
{
    ++CGE::gNumAllocations;
    return CGE::allocate(inSize);
    //return malloc(inSize);
}

void operator delete(void* inData)
{
    ++CGE::gNumReleases;
    CGE::release(inData);
    //free(inData);
}

