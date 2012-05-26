#ifndef C3MACTOR_H
#define C3MACTOR_H

#include "MatrixNode.h"

namespace CGE
{
    class C3MActor
    {
        public:
            C3MActor();
            virtual ~C3MActor();
        protected:
        private:
            Matrix4x4<float> mModelMatrix;
            MatrixNode<float> mModelViewProjectionNode;
    };
}

#endif
