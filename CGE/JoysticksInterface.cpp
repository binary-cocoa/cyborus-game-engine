#include "JoysticksInterface.h"
#include <cassert>

namespace CGE
{
    JoysticksInterface::JoysticksInterface()
    {
        int numJoysticks = SDL_NumJoysticks();

        for (int i = 0; i < numJoysticks; ++i)
            mJoysticks.push_back(new Joystick(i));
    }

    JoysticksInterface::~JoysticksInterface()
    {
        for (size_t i = 0; i < mJoysticks.size(); ++i)
            delete mJoysticks[i];
    }

    const Joystick& JoysticksInterface::joystick(size_t inIndex) const
    {
        assert(inIndex < mJoysticks.size());
        return *mJoysticks[inIndex];
    }

    std::ostream& operator<<(std::ostream& inStream, const JoysticksInterface&
        inJoysticksInterface)
    {
        for (size_t i = 0; i < inJoysticksInterface.numJoysticks(); ++i)
            inStream << inJoysticksInterface.joystick(i) << '\n';

        return inStream;
    }
}
