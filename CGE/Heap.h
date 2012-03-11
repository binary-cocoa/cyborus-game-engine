#ifndef HEAP_H
#define HEAP_H

#include <iostream>

namespace CGE
{
    class Heap
    {
        public:
            Heap(const char* inName);
            ~Heap();

            inline const char* name() const { return mName; }

            void allocate(size_t inBytes);
            void release(size_t inBytes);

            static void dump();
            friend std::ostream& operator<<(std::ostream& inStream,
                const Heap& inHeap);

        protected:
        private:
            const char* const mName;

            size_t mBlocks;
            size_t mBytes;
            size_t mPeakBlocks;
            size_t mPeakBytes;
            size_t mLargestBlock;

            Heap* mNextHeap;

            static Heap* mFirstHeap;
    };
}

#endif
