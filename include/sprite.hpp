#pragma once

#include <SDL.h>
#include "SDL_rect.h"
#include "SDL_render.h"
#include <string>
#include <memory>
#include "animation.hpp"

class Sprite {
public:
    Sprite(SDL_Renderer* renderer, const std::string& texturePath, int x, int y, int width, int height);
    ~Sprite() = default;

    void render(SDL_Renderer* renderer) const;

    void setPosition(int x, int y);
    void setSize(int width, int height);
    void setScale(float scaleX, float scaleY);

    // which part of sprite sheet to render
    void setSourceRect(int x, int y, int w, int h);

    int getX() const { return destinationRect.x; }
    int getY() const { return destinationRect.y; }
    int getWidth() const { return destinationRect.w; }
    int getHeight() const { return destinationRect.h; }

    // raw pointer (non-owning) of anim
    void setAnimation(Animation* anim);
    // update sprite things
    void update(float deltaTime);

    // set wether debug box show sor no
    void setDebugBox(bool show) { this->showDebugBox = show; }
    // whether two obejcts are colliding
    void setColliding(bool colliding) { this->colliding = colliding; }
    // get area of collison box for object
    SDL_Rect getCollisionBox() const { return {destinationRect.x, destinationRect.y, destinationRect.w, destinationRect.h}; }

private:
    SDL_Rect destinationRect; // destination on screen
    SDL_Rect sourceRect;      // part of texture to draw

    // unique texture data
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;

    // non-owning pointer to animation
    Animation* animation = nullptr;

    float scaleX = 1.0f;
    float scaleY = 1.0f;

    bool showDebugBox = false;
    bool colliding = false;
};
