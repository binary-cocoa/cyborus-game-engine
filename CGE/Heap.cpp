#include "Heap.h"
#include <iomanip>
#include <cassert>

namespace CGE
{
    Heap* Heap::mFirstHeap = NULL;

    Heap::Heap(const char* inName) : mName(inName), mBlocks(0), mBytes(0),
        mPeakBlocks(0), mPeakBytes(0), mLargestBlock(0)
    {
        assert(mName && *mName);
        mNextHeap = mFirstHeap;
        mFirstHeap = this;
    }

    Heap::~Heap()
    {
    }

    void Heap::allocate(size_t inBytes)
    {
        assert(inBytes > 0);

        ++mBlocks;
        mBytes += inBytes;

        if (mBlocks > mPeakBlocks) mPeakBlocks = mBlocks;
        if (mBytes > mPeakBytes) mPeakBytes = mBytes;
        if (inBytes > mLargestBlock) mLargestBlock = inBytes;
    }

    void Heap::release(size_t inBytes)
    {
        assert(inBytes > 0);
        assert(mBytes >= inBytes);
        assert(mBlocks > 0);

        --mBlocks;
        mBytes -= inBytes;
    }

    void Heap::dump()
    {
        std::cout << std::setw(10) << "Name"
            << std::setw(10) << "Blocks"
            << std::setw(10) << "(Peak)"
            << std::setw(10) << "Bytes"
            << std::setw(10) << "(Peak)"
            << std::setw(10) << "Biggest"
            << '\n';

        for (size_t i = 0; i < 60; ++i)
            std::cout << '-';

        std::cout << '\n';

        for (Heap* h = mFirstHeap; h; h = h->mNextHeap)
        {
            std::cout << *h << '\n';
        }

        for (size_t i = 0; i < 60; ++i)
            std::cout << '-';

        std::cout << "\n\n";
    }

    std::ostream& operator<<(std::ostream& inStream, const Heap& inHeap)
    {
        inStream << std::setw(10) << inHeap.mName
            << std::setw(10) << inHeap.mBlocks
            << std::setw(10) << inHeap.mPeakBlocks
            << std::setw(10) << inHeap.mBytes
            << std::setw(10) << inHeap.mPeakBytes
            << std::setw(10) << inHeap.mLargestBlock
            ;

        return inStream;
    }
}
