#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Graphics.h"
#include <iostream>

namespace CGE
{
    class Joystick
    {
        public:
            Joystick(int inIndex);
            virtual ~Joystick();

            const char* name() const;
            int axes() const;
            int buttons() const;
            int balls() const;
            int hats() const;

        protected:
        private:
            int mIndex;
            SDL_Joystick* mJoystick;
    };

    std::ostream& operator<<(std::ostream& inStream,
        const Joystick& inJoystick);
}

#endif
