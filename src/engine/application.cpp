#include "application.h"

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_timer.h>

namespace Bulwark
{
    Application::~Application()
    {
        Shutdown();
    }

    int Application::Run()
    {
        if (!Initialize())
        {
            Shutdown();
            return 1;
        }

        Uint64 previousTicks = SDL_GetTicks();

        while (m_running)
        {
            const Uint64 currentTicks = SDL_GetTicks();
            const float deltaTime = static_cast<float>(currentTicks - previousTicks) / 1000.0f;
            previousTicks = currentTicks;

            ProcessEvents();
            Update(deltaTime);
            Render();
        }

        Shutdown();
        return 0;
    }

    bool Application::Initialize()
    {
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s", SDL_GetError());
            return false;
        }

        if (!m_window.Create("Bulwark", 800, 600))
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window: %s", SDL_GetError());
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window.GetNativeHandle(), nullptr);
        if (!m_renderer)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create renderer: %s", SDL_GetError());
            return false;
        }

        m_running = true;
        return true;
    }

    void Application::Shutdown()
    {
        if (m_renderer)
        {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
        }

        m_window.Destroy();
        SDL_Quit();
    }

    void Application::ProcessEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                m_running = false;
            }
        }
    }

    void Application::Update(float deltaTime)
    {
        (void)deltaTime;
    }

    void Application::Render()
    {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);
        SDL_RenderPresent(m_renderer);
    }
}
