#ifndef USERINPUTMANAGER_H
#define USERINPUTMANAGER_H

#include "LuaReference.h"
#include <SDL.h>

#include <map>
#include <string>

namespace CGE
{
    class UserInputManager
    {
        public:
            UserInputManager();
            virtual ~UserInputManager();

            struct Command
            {
                LuaReference callback;
                LuaReference* lastSetAction;
            };


            enum UserInputState
            {
                NORMAL,
                MAP_CALLBACK
            };

            enum UserInputType
            {
                KEYBOARD,
                JOYSTICK_AXIS,
                JOYSTICK_BUTTON,
                JOYSTICK_HAT,
                JOYSTICK_BALL
            };

            //master function for all user input
            void OnUserInput(UserInputType inUserInputType);

        protected:
        private:
            LuaReference mKeyCallbacks[SDLK_LAST];

            std::map<std::string, std::string> mKeyNameToCommandMappings;
            std::map<std::string, std::string> mCommandNameToKeyMappings;
    };
}

#endif // USERINPUTMANAGER_H
