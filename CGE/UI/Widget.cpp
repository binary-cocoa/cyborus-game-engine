#include "Widget.h"
#include <cstring>

namespace CGE
{
    static Heap WidgetHeap("Widget");

    void* Widget::operator new(size_t inSize)
    {
        return allocate(inSize, WidgetHeap);
    }

    void Widget::operator delete(void* inMemory)
    {
        release(inMemory);
    }

    Widget::Widget(bool inCanHaveFocus) : mX(0.0f), mY(0.0f), mRadiusX(0.0f),
        mRadiusY(0.0f), mEnabled(true), mCanHaveFocus(inCanHaveFocus),
        mVisible(true), mModelViewProjection(mMatrix)
    {
        memset(mCCallbacks, 0, sizeof(mCCallbacks));
    }

    Widget::~Widget()
    {
    }

    void Widget::setCallback(Event inEvent, const LuaReference& inCallback)
    {
        if (inEvent != NumEvents) mCallbacks[inEvent] = inCallback;
    }

    void Widget::setCallback(Event inEvent, Callback inCallback, void* inData)
    {
        if (inEvent != NumEvents)
        {
            mCCallbacks[inEvent].callback = inCallback;
            mCCallbacks[inEvent].data = inData;
        }
    }

    void Widget::onEvent(Event inEvent, bool inIsClickCandidate)
    {
        if (inEvent != NumEvents)
        {
            mCallbacks[inEvent].call();

            Listener& l = mCCallbacks[inEvent];
            if (l.callback) l.callback(this, l.data);
        }
    }
}
