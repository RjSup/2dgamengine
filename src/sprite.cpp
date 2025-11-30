#include "sprite.hpp"
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include <SDL_image.h>
#include <iostream>
#include <stdexcept>

Sprite::Sprite(SDL_Renderer* renderer, const std::string& texturePath, int x, int y, int width, int height)
    : texture(nullptr, SDL_DestroyTexture),
      destinationRect{x, y, width, height},
      sourceRect{0, 0, width, height}
{
    if (!renderer) {
        throw std::runtime_error("Sprite constructor: renderer is null!");
    }

    // Load surface
    SDL_Surface* surface = IMG_Load(texturePath.c_str());
    if (!surface) {
        throw std::runtime_error("IMG_Load failed for " + texturePath + ": " + IMG_GetError());
    }

    // Create texture from surface
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);

    // Free the surface immediately after creating the texture
    SDL_FreeSurface(surface);
    surface = nullptr;

    if (!tex) {
        throw std::runtime_error("SDL_CreateTextureFromSurface failed for " + texturePath);
    }

    // Assign to unique_ptr
    texture.reset(tex);
}

void Sprite::setAnimation(Animation* anim) {
    animation = anim;
    if (animation) {
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

    // Render the sprite
    SDL_RenderCopy(renderer, texture.get(), &sourceRect, &destinationRect);

    // Debug box
    if (showDebugBox) {
        SDL_Color color = colliding ? SDL_Color{255, 0, 0, 255} : SDL_Color{0, 255, 0, 255};
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_Rect box = getCollisionBox();
        SDL_RenderDrawRect(renderer, &box);
    }
}

void Sprite::setSourceRect(int x, int y, int w, int h) {
    sourceRect.x = x;
    sourceRect.y = y;
    sourceRect.w = w;
    sourceRect.h = h;
}

void Sprite::setPosition(int x, int y) {
    destinationRect.x = x;
    destinationRect.y = y;
}

void Sprite::setSize(int width, int height) {
    destinationRect.w = width;
    destinationRect.h = height;
}

void Sprite::setScale(float sx, float sy) {
    scaleX = sx;
    scaleY = sy;
    destinationRect.w = static_cast<int>(destinationRect.w * scaleX);
    destinationRect.h = static_cast<int>(destinationRect.h * scaleY);
}
