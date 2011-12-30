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
            TextBox(const Font& inFont);
            virtual ~TextBox();

            virtual void display();

            void setText(const char* inText, Uint8 inRed = 255,
                Uint8 inGreen = 255, Uint8 inBlue = 255);

        protected:
        private:
            const Font& mFont;
            Texture2D mTexture;
            InterleavedVBO mVBO;
    };
}

#endif
