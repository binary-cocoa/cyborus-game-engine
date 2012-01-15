#ifndef LUAINDEXEDRESOURCE_H
#define LUAINDEXEDRESOURCE_H

#include <vector>
#include <cassert>

namespace CGE
{
    template<class T>
    class LuaIndexedResource
    {
        public:
            LuaIndexedResource();
            ~LuaIndexedResource();

            T get(size_t inIndex) const;
            size_t add(T inResource);
            T remove(size_t inIndex);
            T first();
            T next();

        protected:
        private:
            LuaIndexedResource(const LuaIndexedResource<T>& inLIR)
            {
                // no copying
            }

            LuaIndexedResource& operator=(const LuaIndexedResource<T>& inLIR)
            {
                // no copying
                return *this;
            }

            std::vector<size_t> mHoles;
            std::vector<T> mResources;
            size_t mIterator;
    };

    template<class T>
    LuaIndexedResource<T>::LuaIndexedResource() : mIterator(0)
    {
    }

    template<class T>
    LuaIndexedResource<T>::~LuaIndexedResource()
    {
    }

    template<class T>
    T LuaIndexedResource<T>::get(size_t inIndex) const
    {
        return inIndex < mResources.size() ? mResources[inIndex] : NULL;
    }

    template<class T>
    size_t LuaIndexedResource<T>::add(T inResource)
    {
        assert(inResource != NULL);

        size_t outIndex = mResources.size();

        if (mHoles.size() > 0)
        {
            outIndex = mHoles.back();
            mHoles.pop_back();
            mResources[outIndex] = inResource;
        }
        else
        {
            mResources.push_back(inResource);
        }

        return outIndex;
    }

    template<class T>
    T LuaIndexedResource<T>::remove(size_t inIndex)
    {
        T outResource = get(inIndex);

        if (outResource != NULL)
        {
            mResources[inIndex] = NULL;
            mHoles.push_back(inIndex);
        }

        return outResource;
    }

    template<class T>
    T LuaIndexedResource<T>::first()
    {
        mIterator = 0;
        return next();
    }

    template<class T>
    T LuaIndexedResource<T>::next()
    {
        T outResource;

        for (size_t i = mIterator; i < mResources.size(); ++i)
        {
            outResource = mResources[i];

            if (outResource != NULL)
            {
                mIterator = i + 1;
                break;
            }
        }

        return outResource;
    }
}

#endif
