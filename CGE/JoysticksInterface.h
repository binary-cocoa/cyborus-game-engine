#ifndef JOYSTICKSINTERFACE_H
#define JOYSTICKSINTERFACE_H

#include "Joystick.h"
#include <vector>
#include <iostream>

namespace CGE
{
    class JoysticksInterface
    {
        public:
            JoysticksInterface();
            virtual ~JoysticksInterface();

            inline size_t numJoysticks() const { return mJoysticks.size(); }

            const Joystick& joystick(size_t inIndex) const;

        protected:
        private:
            std::vector<Joystick*> mJoysticks;
    };

    std::ostream& operator<<(std::ostream& inStream, const JoysticksInterface&
        inJoysticksInterface);
}

#endif
