#ifndef MATRIXNODE_H
#define MATRIXNODE_H

#include "Matrix4x4.h"
#include <set>
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

            inline const Matrix4x4<T>& localMatrix() const
            {
                return mLocalMatrix;
            }

            inline const Matrix4x4<T>& compositeMatrix() const
            {
                return mCompositeMatrix;
            }

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

            MatrixNode* mParent;
            std::set<MatrixNode*> mChildren;
    };

    template<typename T>
    MatrixNode<T>::MatrixNode(const Matrix4x4<T>& inLocalMatrix)
        : mLocalMatrix(inLocalMatrix)
    {
        mParent = NULL;
    }

    template<typename T>
    MatrixNode<T>::~MatrixNode()
    {
        if (mParent) mParent->removeChildNode(*this);

        for (typename std::set<MatrixNode*>::iterator i = mChildren.begin();
            i != mChildren.end(); ++i)
        {
            (*i)->mParent = NULL;
        }
    }

    template<typename T>
    void MatrixNode<T>::multiplyAll(const Matrix4x4<T>& inMatrix)
    {
        mCompositeMatrix.multiply(inMatrix, mLocalMatrix);

        for (typename std::set<MatrixNode*>::iterator i = mChildren.begin();
            i != mChildren.end(); ++i)
        {
            (*i)->multiplyAll(mCompositeMatrix);
        }
    }

    template<typename T>
    void MatrixNode<T>::addChildNode(MatrixNode& inMatrixNode)
    {
        assert(inMatrixNode.mParent == NULL);
        inMatrixNode.mParent = this;
        mChildren.insert(&inMatrixNode);
    }

    template<typename T>
    void MatrixNode<T>::removeChildNode(MatrixNode& inMatrixNode)
    {
        assert(inMatrixNode.mParent == this);
        inMatrixNode.mParent = NULL;
        mChildren.erase(&inMatrixNode);
    }
}

#endif
