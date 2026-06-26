#ifndef BULWARK_WINDOW_H
#define BULWARK_WINDOW_H

#include <string>
#include <SDL3/SDL.h>

namespace Bulwark
{
    class Window
    {
    public:
        Window() = default;
        ~Window();

        bool Create(const std::string& title, int width, int height);
        void Destroy();

        [[nodiscard]] SDL_Window* GetNativeHandle() const;

        [[nodiscard]] int GetWidth() const;
        [[nodiscard]] int GetHeight() const;

    private:
        SDL_Window* m_window = nullptr;

        int m_width = 0;
        int m_height = 0;
    };
}

#endif //BULWARK_WINDOW_H
