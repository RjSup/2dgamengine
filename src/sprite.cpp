#include "sprite.hpp"
#include <SDL_image.h>
#include <iostream>

Sprite::Sprite(SDL_Renderer* renderer, const std::string& texturePath, int x, int y, int width, int height)
    : texture(nullptr, SDL_DestroyTexture),
      destinationRect{x, y, width, height},
      sourceRect{0, 0, width, height}
{
    // ensure renderer exists
    if (!renderer) {
        throw std::runtime_error("Sprite constructor: renderer is null!");
    }

    // create sdl surface
    SDL_Surface* surface = IMG_Load(texturePath.c_str());
    if (!surface) {
        std::string err = IMG_GetError();
        throw std::runtime_error("IMG_Load failed for " + texturePath + ": " + err);
    }

    // create texture png
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    // SDL_FreeSurface(surface);

    if (!tex) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Texture creation failed");
    }

    texture.reset(tex);
}

void Sprite::setAnimation(std::shared_ptr<Animation> anim) {
    animation = anim;
    if(animation) {
        sourceRect = animation->getFrame();
    }
}

void Sprite::update(float deltaTime) {
    if (animation) {
        animation->update(deltaTime);
        sourceRect = animation->getFrame();
    }
}

void Sprite::render(SDL_Renderer* renderer) const {
    if (!texture || !renderer) {
        std::cerr << "Sprite::render called with null texture or renderer!" << SDL_GetError() << std::endl;
        return;
    }

    // get renderer, texture, source rect, and destination on screen
    SDL_RenderCopy(renderer, texture.get(), &sourceRect, &destinationRect);
}

void Sprite::setSourceRect(int x, int y, int w, int h) {
    sourceRect.x = x;
    sourceRect.y = y;
    sourceRect.w = w;
    sourceRect.h = h;
}

void Sprite::setPosition(int x, int y) {
    // set rect for x and y
    destinationRect.x = x;
    destinationRect.y = y;
}

void Sprite::setSize(int width, int height) {
    // set size for x and y
    destinationRect.w = width;
    destinationRect.h = height;
}

void Sprite::setScale(float sx, float sy) {
    // set scale for x and y
    scaleX = sx;
    scaleY = sy;
    destinationRect.w = static_cast<int>(destinationRect.w * scaleX);
    destinationRect.h = static_cast<int>(destinationRect.h * scaleY);
}
