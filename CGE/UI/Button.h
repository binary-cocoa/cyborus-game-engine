#ifndef BUTTON_H
#define BUTTON_H

#include "../Image.h"
#include "../OpenGL/Texture2D.h"
#include "../OpenGL/InterleavedVBO.h"
#include "Widget.h"

namespace CGE
{
    class Button : public Widget
    {
        public:
            Button(const Image& inImage, float inWidth, float inHeight);
            virtual ~Button();

            void setPosition(float inX, float inY);

            virtual void display();

            virtual void onEvent(Widget::Event inEvent,
                bool inIsClickCandidate);

        protected:
        private:
            Texture2D mTexture;
            InterleavedVBO mVBO;
            GLint mFirst;
    };
}

#endif
