#include "CubeMap.h"

#include <iostream>
using namespace std;

namespace CGE
{
    CubeMap::CubeMap() : Texture(GL_TEXTURE_CUBE_MAP)
    {
    }

    CubeMap::~CubeMap()
    {
    }

    void CubeMap::loadImages(const Image& inPositiveX, const Image& inNegativeX,
        const Image& inPositiveY, const Image& inNegativeY,
        const Image& inPositiveZ, const Image& inNegativeZ)
    {
        const GLenum params1[] = {
            GL_TEXTURE_MAG_FILTER, GL_LINEAR,
            GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE,
            GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE,
            GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE,
            0 };

        const GLenum params2[] = {
            GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR,
            0 };

        bind();
        processParams(params1);

        inPositiveX.loadIntoTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X);
        inNegativeX.loadIntoTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
        inPositiveY.loadIntoTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
        inNegativeY.loadIntoTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
        inPositiveZ.loadIntoTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
        inNegativeZ.loadIntoTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

        glGenerateMipmap(mTarget);
        processParams(params2);
    }
}
