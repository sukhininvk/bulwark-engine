#ifndef BULWARKENGINE_INPUT_H
#define BULWARKENGINE_INPUT_H

#include <SDL3/SDL_events.h>

namespace Bulwark
{
    class Input
    {
    public:
        static void HandleEvent(const SDL_Event& event);
    };
}

#endif //BULWARKENGINE_INPUT_H
