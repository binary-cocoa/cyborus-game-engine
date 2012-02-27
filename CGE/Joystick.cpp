#include "Joystick.h"

namespace CGE
{
    Joystick::Joystick(int inIndex) : mIndex(inIndex)
    {
        mJoystick = SDL_JoystickOpen(mIndex);
    }

    Joystick::~Joystick()
    {
        if (SDL_JoystickOpened(mIndex))
            SDL_JoystickClose(mJoystick);
    }

    const char* Joystick::name() const
    {
        return SDL_JoystickName(mIndex);
    }

    int Joystick::axes() const
    {
        return SDL_JoystickNumAxes(mJoystick);
    }

    int Joystick::buttons() const
    {
        return SDL_JoystickNumButtons(mJoystick);
    }

    int Joystick::balls() const
    {
        return SDL_JoystickNumBalls(mJoystick);
    }

    int Joystick::hats() const
    {
        return SDL_JoystickNumHats(mJoystick);
    }

    std::ostream& operator<<(std::ostream& inStream, const Joystick& inJoystick)
    {
        inStream << inJoystick.name() << " (";

        int axes = inJoystick.axes();
        if (axes < 0) axes = 0;
        inStream << axes << " ax" << (axes == 1 ? "is" : "es");

        int buttons = inJoystick.buttons();
        if (buttons > 0)
        {
            inStream << ", " << buttons << " button";
            if (buttons != 1) inStream << 's';
        }

        int balls = inJoystick.balls();
        if (balls > 0)
        {
            inStream << ", " << balls << " ball";
            if (balls != 1) inStream << 's';
        }

        int hats = inJoystick.hats();
        if (hats > 0)
        {
            inStream << ", " << hats << " hat";
            if (hats != 1) inStream << 's';
        }

        inStream << ")";

        return inStream;
    }
}
