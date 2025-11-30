#include "collider.hpp"
#include "SDL_rect.h"
#include "sprite.hpp"

// Add a sprite to collider (non-owning)
void Collider::addSprite(Sprite* sprite) {
    if (sprite) {
        sprites.push_back(sprite); // raw pointer, collider does not own it
    }
}

// Check collision between two SDL_Rects
bool Collider::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return !(a.x + a.w <= b.x || a.x >= b.x + b.w ||
             a.y + a.h <= b.y || a.y >= b.y + b.h);
}

// Update collision status for all sprites
void Collider::update() {
    for (auto& s : sprites) {
        if (!s) continue;

        SDL_Rect box = s->getCollisionBox();
        bool colliding = false;

        // Check collision with every other sprite
        for (auto& other : sprites) {
            if (other && other != s) {
                if (checkCollision(box, other->getCollisionBox())) {
                    colliding = true;
                    break;
                }
            }
        }

        s->setColliding(colliding);
        s->setDebugBox(debugMode);
    }
}

void Collider::conflictResolution(Sprite* sprite1, Sprite* sprite2) {

}
