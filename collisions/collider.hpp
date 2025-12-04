#pragma once
#include <vector>
#include <memory>
#include "sprite.hpp"

class Collider {
public:
    Collider() = default;
    ~Collider() = default;

    void add_sprite(const std::shared_ptr<Sprite>& sprite);
    // removes a sprite from the collision bounds
    void remove_sprite(Sprite* sprite);
    // updates collider based on location and if colliding
    void update();
    // set whether debug mode should be on or off
    void set_debug_mode(bool enabled) { debug_mode = enabled; }
    // whether the mode is on or no
    bool is_debug_mode() const { return debug_mode; }

private:
// store weak_ptrs to avoid ownership cycles
    std::vector<std::weak_ptr<Sprite>> sprites;
    bool debug_mode = false;

    // whether the player sprite rect collides with an enemy sprite rect
    bool check_collision(const SDL_Rect& a, const SDL_Rect& b);
};
