#include "background.hpp"

Background::Background(SDL_Texture* background_texture, int width, int height)
    : texture(background_texture)
{
    rect = { 0, 0, width, height };
}

Background::~Background() {
    SDL_DestroyTexture(texture);
}

void Background::render(SDL_Renderer* renderer) {

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
