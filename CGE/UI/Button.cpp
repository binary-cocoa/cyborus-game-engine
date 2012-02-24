#include "Button.h"

namespace CGE
{
    Button::Button(const Image& inImage, float inWidth, float inHeight)
        : mFirst(0)
    {
        mTexture.loadImage(inImage);

        const float Min = 0.1f;
        if (inWidth < Min) inWidth = Min;
        if (inHeight < Min) inHeight = Min;

        mRadiusX = inWidth / 2.0f;
        mRadiusY = inHeight / 2.0f;

        mVBO.addField(0, 2); // Vertices (XY bound on attrib 0)
        mVBO.addField(1, 2); // Texture Coordinates (ST bound on attrib 1)

        GLfloat data[4 * 4 * (2 + 2)]; // 4 states of 4 vertices with XY and ST
        GLfloat* d = data;

        for (size_t i = 0; i < 4; ++i)
        {
            float tcy = float(i) * 0.25f;
            *d++ = mRadiusX;
            *d++ = mRadiusY;
            *d++ = 1.0f;
            *d++ = tcy;

            *d++ = mRadiusX;
            *d++ = -mRadiusY;
            *d++ = 1.0f;
            *d++ = tcy + 0.25f;

            *d++ = -mRadiusX;
            *d++ = -mRadiusY;
            *d++ = 0.0f;
            *d++ = tcy + 0.25f;

            *d++ = -mRadiusX;
            *d++ = mRadiusY;
            *d++ = 0.0f;
            *d++ = tcy;
        }

        mVBO.loadData(data, 4 * 4);

        setPosition(0.0f, 0.0f);
    }

    Button::~Button()
    {
    }

    void Button::setPosition(float inX, float inY)
    {
        mX = inX;
        mY = inY;

        mTransform.loadIdentity();
        mTransform.translate(mX, mY, 0.0f);
    }


    void Button::display()
    {
        mTexture.bind();
        mVBO.display(GL_TRIANGLE_FAN, mFirst, 4);
    }

    void Button::onEvent(Widget::Event inEvent, bool inIsClickCandidate)
    {
        Widget::onEvent(inEvent, inIsClickCandidate);

        switch (inEvent)
        {
            case Widget::MouseIn:
            {
                mFirst = isEnabled() ? (inIsClickCandidate ? 8 : 4) : 12;
                break;
            }

            case Widget::MouseOut:
            {
                mFirst = isEnabled() ? 0 : 12;
                break;
            }

            case Widget::MouseDown:
            {
                mFirst = isEnabled() ? 8 : 12;
                break;
            }

            case Widget::MouseUp:
            {
                mFirst = isEnabled() ? 4 : 12;
                break;
            }

            default: {}
        }
    }
}
