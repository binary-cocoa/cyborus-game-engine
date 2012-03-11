#include "LuaMachine.h"
#include "Memory.h"
#include <iostream>

namespace CGE
{
    static Heap LuaHeap("Lua");

    void* LuaMachine::allocateLuaBlock(void* inUserData, void* inPointer,
        size_t inOldSize, size_t inNewSize)
    {
        (void)inOldSize;

        void* outBlock = NULL;

        if (inNewSize > 0)
        {
            outBlock = reallocate(inPointer, inNewSize, LuaHeap);
        }
        else
        {
            release(inPointer);
        }

        return outBlock;
    }

    LuaMachine::LuaMachine() : mLuaState(NULL)
    {
        reset();
    }

    LuaMachine::~LuaMachine()
    {
        lua_close(mLuaState);
        std::cout << mAllocations << " allocations, "
            << mReleases << " releases\n";
    }

    void LuaMachine::reset()
    {
        if (mLuaState) lua_close(mLuaState);
        mLuaState = lua_newstate(allocateLuaBlock, this);
        luaL_openlibs(mLuaState);
    }

    void LuaMachine::addFunction(const char* inName, lua_CFunction inFunction)
    {
        lua_register(mLuaState, inName, inFunction);
    }

    void LuaMachine::reportErrors()
    {
        if (mStatus)
        {
            mError = "-- ";
            mError += lua_tostring(mLuaState, -1);
            std::cerr << mError << '\n';
            lua_pop(mLuaState, 1); // remove error message
        }
    }

    void LuaMachine::execute()
    {
        mStatus = lua_pcall(mLuaState, 0, LUA_MULTRET, 0);
        if (mStatus) reportErrors();
    }

    void LuaMachine::loadFile(const char* inFile)
    {
        mStatus = luaL_loadfile(mLuaState, inFile);
        if (mStatus)
            reportErrors();
        else
            execute();
    }

    void LuaMachine::runCommand(const char* inCommand)
    {
        mStatus = luaL_loadstring(mLuaState, inCommand);
        if (mStatus)
            reportErrors();
        else
            execute();
    }
}
