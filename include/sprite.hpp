#pragma once

#include <SDL.h>
#include "SDL_render.h"
#include "animation.hpp"
#include <string>
#include <memory>

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

        void setAnimation(std::shared_ptr<Animation> anim);
        void update(float deltaTime);

    private:
        // dest on screen of sprite
        SDL_Rect destinationRect;
        // part of the texture to draw
        SDL_Rect sourceRect;
        // unique texture data
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;
        // share the animation pointer - it can change
        std::shared_ptr<Animation> animation;

        float scaleX = 1.0f;
        float scaleY = 1.0f;
};
