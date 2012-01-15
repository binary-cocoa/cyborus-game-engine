#ifndef REFERENCE_H
#define REFERENCE_H

#include <cstdlib>

namespace CGE
{
    template<class T>
    class Reference
    {
        class Container
        {
            public:
                Container(T* inPointer = NULL) : mPointer(inPointer), mCount(1)
                {
                }

                inline ~Container() { delete mPointer; }

                inline void acquire()
                {
                    if (mPointer) ++mCount;
                }

                inline void release()
                {
                    if (mPointer && !--mCount) delete this;
                }

                inline T* pointer() { return mPointer; }
                inline const T* pointer () const { return mPointer; }

            private:
                T* mPointer;
                size_t mCount;
        };

        static Container NullReference;

        public:
            Reference(T* inPointer = NULL) : mContainer(&NullReference)
            {
                if (inPointer) mContainer = new Container(inPointer);
            }

            Reference(const Reference& inReference)
            {
                mContainer = inReference.mContainer;
                mContainer->acquire();
            }

            inline ~Reference()
            {
                mContainer->release();
            }

            inline operator T*()
            {
                return mContainer->pointer();
            }

            inline operator const T*() const
            {
                return mContainer->pointer();
            }

            inline T* operator->()
            {
                return mContainer->pointer();
            }

            inline const T* operator->() const
            {
                return mContainer->pointer();
            }

            inline T& operator*() { return *mContainer->pointer(); }
            inline const T& operator*() const { return *mContainer->pointer(); }

            Reference& operator=(T* inPointer)
            {
                mContainer->release();

                if (inPointer)
                    mContainer = new Container(inPointer);
                else
                    mContainer = &NullReference;

                return *this;
            }

            Reference& operator=(const Reference& inReference)
            {
                mContainer->release();
                mContainer = inReference.mContainer;
                mContainer->acquire();
                return *this;
            }

            inline bool operator==(const Reference& inReference) const
            {
                return mContainer == inReference.mContainer;
            }

            inline bool operator!=(const Reference& inReference) const
            {
                return mContainer != inReference.mContainer;
            }

            inline bool operator==(const T* inPointer) const
            {
                return mContainer->pointer() == inPointer;
            }

            inline bool operator!=(const T* inPointer) const
            {
                return mContainer->pointer() != inPointer;
            }

        private:
            Container* mContainer;
    };

    template<class T>
    typename Reference<T>::Container Reference<T>::NullReference;
}

#endif
