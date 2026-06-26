#ifndef BULWARK_APPLICATION_H
#define BULWARK_APPLICATION_H

#include "window.h"

#include <SDL3/SDL.h>

namespace Bulwark {
    class Application
    {
    public:
        Application() = default;
        ~Application();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        int Run();

    private:
        bool Initialize();
        void Shutdown();
        void ProcessEvents();
        static void Update(float deltaTime);
        void Render();

        bool m_running = true;
        Window m_window;
        SDL_Renderer* m_renderer = nullptr;
    };
}

#endif //BULWARK_APPLICATION_H
