#include "Actor.h"
#include "Memory.h"

namespace CGE
{
    static Heap ActorHeap("Actor");

    void* Actor::operator new(size_t inSize)
    {
        return allocate(inSize, ActorHeap);
    }

    void Actor::operator delete(void* inMemory)
    {
        release(inMemory);
    }

    Actor::Actor(Model* inModel) : mModel(inModel), mHead(NULL),
        mNextActor(NULL), mPreviousActor(NULL)
    {
    }

    Actor::~Actor()
    {
        removeFromBin();
    }

    void Actor::removeFromBin()
    {
        if (mHead)
        {
            *mHead = mNextActor;
            if (mNextActor) mNextActor->mHead = mHead;
            mHead = NULL;
        }

        if (mPreviousActor) mPreviousActor->mNextActor = mNextActor;
        if (mNextActor) mNextActor->mPreviousActor = mPreviousActor;

        mPreviousActor = NULL;
        mNextActor = NULL;
    }

    void Actor::display()
    {
        mModel->display();
    }
}
