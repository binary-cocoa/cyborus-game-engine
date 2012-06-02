#include "TextBox.h"
#include "../Image.h"

#include <iostream>

namespace CGE
{
    const float TextBox::Left = 0.0f;
    const float TextBox::Center = 0.5f;
    const float TextBox::Right = 1.0f;

    const float TextBox::Top = 0.0f;
    const float TextBox::Middle = 0.5f;
    const float TextBox::Bottom = 1.0f;

    TextBox::TextBox(float inHeight) : mWidth(0.0f), mHeight(inHeight),
        mVerticalAlignment(0.0f), mHorizontalAlignment(0.0f)
    {
        const float MinHeight = 0.01f;
        if (mHeight < MinHeight) mHeight = MinHeight;

        mVBO.addField(0, 2); // Vertices (XY bound on attrib 0)
        mVBO.addField(1, 2); // Texture Coordinates (ST bound on attrib 1)

        GLfloat data[4 * (2 + 2)]; // 4 vertices with XY and ST
        GLfloat* d = data;

        *d++ = 1.0f;
        *d++ = 1.0f;
        *d++ = 1.0f;
        *d++ = 0.0f;

        *d++ = 1.0f;
        *d++ = -1.0f;
        *d++ = 1.0f;
        *d++ = 1.0f;

        *d++ = -1.0f;
        *d++ = -1.0f;
        *d++ = 0.0f;
        *d++ = 1.0f;

        *d++ = -1.0f;
        *d++ = 1.0f;
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

    void TextBox::setPosition(float inX, float inY, float inVerticalAlignment,
        float inHorizontalAlignment)
    {
        mTarget[0] = inX;
        mTarget[1] = inY;

        mVerticalAlignment = inVerticalAlignment;
        lockRange(mVerticalAlignment);

        mHorizontalAlignment = inHorizontalAlignment;
        lockRange(mHorizontalAlignment);

        update();
    }

    void TextBox::setText(const Font& inFont, const char* inText, Uint8 inRed,
        Uint8 inGreen, Uint8 inBlue)
    {
        Image textImage;

        textImage.loadText(inFont, inText, inRed, inGreen, inBlue);

        if (textImage.isValid())
        {
            float ratio = mHeight / float(textImage.height());

            Image textureImage;
            textureImage.powersOfTwoRectangleFrom(textImage);

            mExcess[0] = float(textureImage.width() - textImage.width())
                * ratio / 2.0f;

            mExcess[1] = float(textureImage.height() - textImage.height())
                * ratio / 2.0f;

            mWidth = float(textImage.width()) * ratio;
            update();

            mTexture.loadImage(textureImage);
        }
    }

    void TextBox::update()
    {
        mRadiusX = mWidth / 2.0f;
        mRadiusY = mHeight / 2.0f;

        float inverseH = 1.0f - mHorizontalAlignment;
        float inverseV = 1.0f - mVerticalAlignment;

        float leftEdge = mTarget[0] - (mHorizontalAlignment * mWidth);
        float rightEdge = mTarget[0] + (inverseH * mWidth);
        mX = (leftEdge + rightEdge) / 2.0f;

        float bottomEdge = mTarget[1] - (mVerticalAlignment * mHeight);
        float topEdge = mTarget[1] + (inverseV * mHeight);
        mY = (topEdge + bottomEdge) / 2.0f;

        mMatrix.loadIdentity();
        mMatrix.translate(mX + mExcess[0], mY + mExcess[1], 0.0f);
        mMatrix.scale(mRadiusX + mExcess[0], mRadiusY + mExcess[1], 0.0f);
    }

    void TextBox::lockRange(float& inValue)
    {
        if (inValue < 0.0f)
            inValue = 0.0f;
        else if (inValue > 1.0f)
            inValue = 1.0f;
    }
}
