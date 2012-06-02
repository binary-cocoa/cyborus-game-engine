#ifndef MATRIXNODE_H
#define MATRIXNODE_H

#include "Matrix4x4.h"
#include <cassert>

namespace CGE
{
    template<typename T>
    class MatrixNode
    {
        public:
            MatrixNode(const Matrix4x4<T>& inLocalMatrix);
            virtual ~MatrixNode();

            void multiplyAll(const Matrix4x4<T>& inMatrix);
            void addChildNode(MatrixNode& inMatrixNode);
            void removeChildNode(MatrixNode& inMatrixNode);
            void detach();

            inline const Matrix4x4<T>& localMatrix() const
            {
                return mLocalMatrix;
            }

            inline const Matrix4x4<T>& compositeMatrix() const
            {
                return mCompositeMatrix;
            }

            inline const size_t childCount() const { return mCount; }

        private:
            MatrixNode(const MatrixNode& inMatrixNode)
            {
                // no copying
            }

            MatrixNode& operator=(const MatrixNode& inMatrixNode)
            {
                // no copying
                return *this;
            }

            const Matrix4x4<T>& mLocalMatrix;
            Matrix4x4<T> mCompositeMatrix;

            size_t mCount;
            MatrixNode* mParent;
            MatrixNode* mFirstChild;
            MatrixNode* mNext;
            MatrixNode* mPrevious;
    };

    template<typename T>
    MatrixNode<T>::MatrixNode(const Matrix4x4<T>& inLocalMatrix)
        : mLocalMatrix(inLocalMatrix)
    {
        mCount = 0;
        mParent = NULL;
        mFirstChild = NULL;
        mNext = NULL;
        mPrevious = NULL;
    }

    template<typename T>
    MatrixNode<T>::~MatrixNode()
    {
        detach();

        for (MatrixNode* i = mFirstChild; i; i = i->mNext)
        {
            i->mParent = NULL;
            i->mNext = NULL;
            i->mPrevious = NULL;
        }
    }

    template<typename T>
    void MatrixNode<T>::multiplyAll(const Matrix4x4<T>& inMatrix)
    {
        mCompositeMatrix.multiply(inMatrix, mLocalMatrix);

        for (MatrixNode* i = mFirstChild; i; i = i->mNext)
            i->multiplyAll(mCompositeMatrix);
    }

    template<typename T>
    void MatrixNode<T>::addChildNode(MatrixNode& inMatrixNode)
    {
        assert(inMatrixNode.mParent == NULL);
        assert(inMatrixNode.mNext == NULL);
        assert(inMatrixNode.mPrevious == NULL);
        ++mCount;
        inMatrixNode.mParent = this;

        if (mFirstChild)
        {
            inMatrixNode.mNext = mFirstChild;
            assert(mFirstChild->mPrevious == NULL);
            mFirstChild->mPrevious = &inMatrixNode;
        }

        mFirstChild = &inMatrixNode;
    }

    template<typename T>
    void MatrixNode<T>::removeChildNode(MatrixNode& inMatrixNode)
    {
        assert(inMatrixNode.mParent == this);
        --mCount;

        if (mFirstChild == &inMatrixNode)
        {
            mFirstChild = inMatrixNode.mNext;

            if (mFirstChild)
            {
                assert(mFirstChild->mPrevious == &inMatrixNode);
                mFirstChild->mPrevious = NULL;
            }
        }
        else
        {
            assert(inMatrixNode.mPrevious != NULL);
            inMatrixNode.mPrevious->mNext = inMatrixNode.mNext;

            if (inMatrixNode.mNext)
                inMatrixNode.mNext->mPrevious = inMatrixNode.mPrevious;
        }

        inMatrixNode.mParent = NULL;
        inMatrixNode.mNext = NULL;
        inMatrixNode.mPrevious = NULL;
    }

    template<typename T>
    void MatrixNode<T>::detach()
    {
        if (mParent) mParent->removeChildNode(*this);
    }
}

#endif
