#pragma once

#include <SDL_render.h>
#include <memory>
#include "window.hpp"

class Renderer {
    public:
        Renderer(const Window& window);
        ~Renderer() = default;

        SDL_Renderer* get() const { return renderer.get(); }

        void set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
        void clear();
        void present();

    private:
        // <sdl_renderer - type of the object
        // void(*)(sdl_renderer*) - how to delete it
        // must be known at compile time
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
};
