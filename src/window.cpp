#include "window.hpp"
#include "SDL_video.h"
#include <SDL.h>
#include <stdexcept>

Window::Window(const std::string& title, int width, int height)
    : window(
        SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_SHOWN),
        SDL_DestroyWindow)
{
    if (!window) {
        throw std::runtime_error("SDL_CreateWindow failed");
    }
}
