#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Widget.h"
#include "../Graphics.h"
#include "../Font.h"
#include "../OpenGL/Texture2D.h"
#include "../OpenGL/InterleavedVBO.h"

namespace CGE
{
    class TextBox : public Widget
    {
        public:
            static const float Left;
            static const float Center;
            static const float Right;

            static const float Top;
            static const float Middle;
            static const float Bottom;

            TextBox(float inHeight = 0.5f);
            virtual ~TextBox();

            virtual void display();

            void setPosition(float inX, float inY,
                float inVerticalAlignment = Middle,
                float inHorizontalAlignment = Left);
            void setText(const Font& inFont, const char* inText,
                Uint8 inRed = 255, Uint8 inGreen = 255, Uint8 inBlue = 255);

        protected:
        private:
            void update();

            float mWidth;
            float mHeight;
            float mVerticalAlignment;
            float mHorizontalAlignment;

            vec2f mTarget;
            vec2f mExcess;

            Texture2D mTexture;
            InterleavedVBO mVBO;

            static void lockRange(float& inValue);
    };
}

#endif
