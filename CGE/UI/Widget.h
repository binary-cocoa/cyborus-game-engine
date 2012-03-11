#ifndef WIDGET_H
#define WIDGET_H

#include "../SceneGraphNode.h"
#include "../LuaReference.h"
#include "../Memory.h"

namespace CGE
{
    class Widget : public SceneGraphNode
    {
        public:
            typedef void (*Callback)(Widget*, void*);

            struct Listener
            {
                Callback callback;
                void* data;
            };

            enum Event { MouseIn, MouseOut, MouseDown, MouseUp, MouseClick,
                Focus, Blur, NumEvents };

            Widget(bool inCanHaveFocus = true);
            virtual ~Widget();

            virtual void display() = 0;

            inline void enable(bool inEnabled = true)
            {
                mEnabled = inEnabled;
            }

            inline void disable()
            {
                mEnabled = false;
            }

            inline bool isEnabled()
            {
                return mEnabled;
            }

            inline bool isDisabled()
            {
                return !mEnabled;
            }

            inline bool canHaveFocus() const
            {
                return mEnabled && mCanHaveFocus;
            }

            inline bool contains(float inX, float inY) const
            {
                return inX >= mX - mRadiusX
                    && inX <= mX + mRadiusX
                    && inY >= mY - mRadiusY
                    && inY <= mY + mRadiusY;
            }

            virtual void onEvent(Event inEvent, bool inIsClickCandidate);
            void setCallback(Event inEvent, const LuaReference& inCallback);
            void setCallback(Event inEvent, Callback inCallback,
                void* inData = NULL);

            static void* operator new(size_t inSize);
            static void operator delete(void* inMemory);

        protected:
            float mX;
            float mY;
            float mRadiusX;
            float mRadiusY;

        private:
            bool mEnabled;
            bool mCanHaveFocus;
            bool mVisible;

            LuaReference mCallbacks[NumEvents];
            Listener mCCallbacks[NumEvents];

    };
}

#endif
