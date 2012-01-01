#ifndef LUAREFERENCE_H
#define LUAREFERENCE_H

#include <lua.hpp>

namespace CGE
{
    class LuaReference
    {
        public:
            LuaReference(lua_State* inState = NULL);
            ~LuaReference();

            inline bool isSet() const { return mReference != LUA_NOREF; }
            inline operator bool() const { return isSet(); }

            void unset();
            void set(lua_State* inState);
            bool get() const;

        protected:
        private:
            lua_State* mState;
            int mReference;
    };
}

#endif
