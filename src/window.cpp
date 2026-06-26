#include "window.h"

namespace Bulwark
{
    Window::~Window()
    {
        Destroy();
    }

    bool Window::Create(const std::string& title, const int width, const int height)
    {
        m_width = width;
        m_height = height;

        m_window = SDL_CreateWindow(
            title.c_str(),
            width,
            height,
            0
        );

        return m_window != nullptr;
    }

    void Window::Destroy()
    {
        if (m_window)
        {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }
    }

    SDL_Window* Window::GetNativeHandle() const
    {
        return m_window;
    }

    int Window::GetWidth() const
    {
        return m_width;
    }

    int Window::GetHeight() const
    {
        return m_height;
    }
}
