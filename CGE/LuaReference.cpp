#include "LuaReference.h"
#include <cassert>

namespace CGE
{
    LuaReference::LuaReference(lua_State* inState) : mState(NULL),
        mReference(LUA_NOREF)
    {
        if (inState) set(inState);
    }

    LuaReference::LuaReference(const LuaReference& inLuaReference)
        : mState(NULL), mReference(LUA_NOREF)
    {
        copyFrom(inLuaReference);
    }

    LuaReference::~LuaReference()
    {
        unset();
    }

    LuaReference& LuaReference::operator=(const LuaReference& inLuaReference)
    {
        copyFrom(inLuaReference);
        return *this;
    }

    void LuaReference::set(lua_State* inState)
    {
        assert(inState != NULL);
        unset();

        mState = inState;
        mReference = luaL_ref(mState, LUA_REGISTRYINDEX);

        if (mReference == LUA_REFNIL)
        {
            mReference = LUA_NOREF;
            mState = NULL;
        }
    }

    // Returns whether this LuaReference is set. This prevents having to do
    // two checks via:
    //     if (ref.isSet()) ref.get(); // Checks again inside the get function.
    bool LuaReference::get() const
    {
        if (isSet())
        {
            lua_rawgeti(mState, LUA_REGISTRYINDEX, mReference);
            return true;
        }

        return false;
    }

    void LuaReference::unset()
    {
        if (isSet())
        {
            assert(mState != NULL);
            luaL_unref(mState, LUA_REGISTRYINDEX, mReference);
            mState = NULL;
            mReference = LUA_NOREF;
        }
    }

    void LuaReference::copyFrom(const LuaReference& inLuaReference)
    {
        if (inLuaReference.get()) set(inLuaReference.mState);
    }
}
