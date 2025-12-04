#pragma once

#include <SDL_video.h>
#include <memory>
#include <string>

class Window {
    public:
        Window(const std::string& title, int width, int height);
        ~Window() = default;

        SDL_Window* get() const { return window.get(); }

    private:
        // <sdl_window - type of the object
        // void(*)(sdl_window*) - how to delete it
        // must be known at compile time - can't delete incomplete type
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
};
