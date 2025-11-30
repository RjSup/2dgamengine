#pragma once

#include <vector>
#include "SDL_rect.h"

class Sprite;

class Collider {
public:
    Collider() : debugMode(false) {}
    ~Collider() = default;

    // if debug mode should be allowed or not
    void setDebugMode(bool enabled) { debugMode = enabled; }

    // add sprites to collider
    void addSprite(Sprite* sprite);

    // update collider state
    void update();

private:
    // raw pointer to array of sprites
    std::vector<Sprite*> sprites;
    bool debugMode;

    // check if to rects collide
    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
    // what should happen if they do
    void conflictResolution(Sprite* sprite1, Sprite* sprite2);
};
