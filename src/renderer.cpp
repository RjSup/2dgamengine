#include "renderer.hpp"
#include <SDL.h>
#include <stdexcept>

Renderer::Renderer(const Window& window)
    : renderer(
        SDL_CreateRenderer(
            window.get(),
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            SDL_DestroyRenderer)
{
    if (!renderer) {
        throw std::runtime_error("Failed to create SDL_Renderer");
    }
}

void Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer.get(), r, g, b, a);
}

void Renderer::clear()
{
    SDL_RenderClear(renderer.get());
}

void Renderer::present()
{
    SDL_RenderPresent(renderer.get());
}
