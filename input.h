#pragma once

#define NKEYS 256

namespace input
{
    namespace keyboard
    {
        extern bool keystates[NKEYS];
    }

    namespace mouse
    {
        extern int x, y;
        extern int relativeX, relativeY;
        extern bool leftButton, rightButton;
    }
}
