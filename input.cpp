#include "input.h"

namespace input
{
    namespace keyboard
    {
        bool keystates[NKEYS] = {false};
    }

    namespace mouse
    {
        int x = 0, y = 0;
        int relativeX = 0, relativeY = 0;
        bool leftButton = false, rightButton = false;
    }
}
