#ifndef REFERENCE_H
#define REFERENCE_H

#include <cstdlib>
#include "Memory.h"

namespace CGE
{
    template<class T>
    class Reference
    {
        public:
            Reference(T* inPointer = NULL) : mPointer(inPointer)
            {
                addReference(mPointer);
            }

            Reference(const Reference& inReference)
            {
                mPointer = inReference.mPointer;
                addReference(mPointer);
            }

            inline ~Reference()
            {
                if (removeReference(mPointer) < 1) delete mPointer;
            }

            inline operator T*()
            {
                return mPointer;
            }

            inline operator const T*() const
            {
                return mPointer;
            }

            inline T* operator->()
            {
                return mPointer;
            }

            inline const T* operator->() const
            {
                return mPointer;
            }

            inline T& operator*() { return *mPointer; }
            inline const T& operator*() const { return *mPointer; }

            Reference& operator=(T* inPointer)
            {
                if (removeReference(mPointer) < 1) delete mPointer;
                mPointer = inPointer;
                addReference(mPointer);
                return *this;
            }

            Reference& operator=(const Reference& inReference)
            {
                if (removeReference(mPointer) < 1) delete mPointer;
                mPointer = inReference.mPointer;
                addReference(mPointer);
                return *this;
            }

            inline bool operator==(const Reference& inReference) const
            {
                return mPointer == inReference.mPointer;
            }

            inline bool operator!=(const Reference& inReference) const
            {
                return mPointer != inReference.mPointer;
            }

            inline bool operator==(const T* inPointer) const
            {
                return mPointer == inPointer;
            }

            inline bool operator!=(const T* inPointer) const
            {
                return mPointer != inPointer;
            }

        private:
            T* mPointer;
    };
}

#endif
