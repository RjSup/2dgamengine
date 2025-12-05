#pragma once
#include "SDL_rect.h"
#include "SDL_render.h"
#include <SDL.h>

class Background {
public:
    Background(SDL_Texture* background_texture, int width, int height);
    ~Background();

    void render(SDL_Renderer* render);

private:
    SDL_Texture* texture = nullptr;
    SDL_Rect rect;

};
