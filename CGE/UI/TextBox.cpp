#include "TextBox.h"
#include "../Image.h"

namespace CGE
{
    TextBox::TextBox(const Font& inFont) : mFont(inFont)
    {
        mRadiusX = 2.0f;
        mRadiusY = 0.5f;

        mVBO.addField(0, 2); // Vertices (XY bound on attrib 0)
        mVBO.addField(1, 2); // Texture Coordinates (ST bound on attrib 1)

        GLfloat data[4 * (2 + 2)]; // 4 vertices with XY and ST
        GLfloat* d = data;

        *d++ = mRadiusX;
        *d++ = mRadiusY;
        *d++ = 1.0f;
        *d++ = 0.0f;

        *d++ = mRadiusX;
        *d++ = -mRadiusY;
        *d++ = 1.0f;
        *d++ = 1.0f;

        *d++ = -mRadiusX;
        *d++ = -mRadiusY;
        *d++ = 0.0f;
        *d++ = 1.0f;

        *d++ = -mRadiusX;
        *d++ = mRadiusY;
        *d++ = 0.0f;
        *d++ = 0.0f;

        mVBO.loadData(data, 4);
    }

    TextBox::~TextBox()
    {
    }

    void TextBox::display()
    {
        mTexture.bind();
        mVBO.display(GL_TRIANGLE_FAN, 0, 4);
    }

    void TextBox::setText(const char* inText, Uint8 inRed, Uint8 inGreen,
        Uint8 inBlue)
    {
        Image textImage;

        textImage.loadText(mFont, inText, inRed, inGreen, inBlue);

        mTexture.loadImage(textImage);
    }
}
