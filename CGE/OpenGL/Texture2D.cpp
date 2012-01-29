#include "Texture2D.h"

namespace CGE
{
    Texture2D::Texture2D() : Texture(GL_TEXTURE_2D)
    {
    }

    Texture2D::Texture2D(const Image& inImage) : Texture(GL_TEXTURE_2D)
    {
        loadImage(inImage);
    }

    Texture2D::~Texture2D()
    {
    }

    void Texture2D::loadImage(const Image& inImage, GLenum inEdgeMode,
        bool inEnableMipmapping)
    {
        bind();

        if (inEnableMipmapping)
        {
            const GLenum params1[] = {
                GL_TEXTURE_WRAP_S, inEdgeMode,
                GL_TEXTURE_WRAP_T, inEdgeMode,
                GL_TEXTURE_MAG_FILTER, GL_LINEAR,
                0 };

            const GLenum params2[] = {
                GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR,
                0 };

            processParams(params1);
            inImage.loadIntoTexture(mTarget);
            glGenerateMipmap(mTarget);
            processParams(params2);
        }
        else
        {
            const GLenum params[] = {
                GL_TEXTURE_WRAP_S, inEdgeMode,
                GL_TEXTURE_WRAP_T, inEdgeMode,
                GL_TEXTURE_MAG_FILTER, GL_LINEAR,
                GL_TEXTURE_MIN_FILTER, GL_LINEAR,
                0 };

            processParams(params);
            inImage.loadIntoTexture(mTarget);
        }
    }
}
