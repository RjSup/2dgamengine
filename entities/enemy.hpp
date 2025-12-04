#pragma once
#include "sprite.hpp"

class Enemy : public Sprite {
public:
    Enemy(SDL_Renderer* renderer, const std::string& path, int x, int y, int width, int height);
    // move the enemy based on deltaTime
    void update_movement(float delta_time);

    // where the enemy will move
    void set_patrol_bounds(int min_x, int max_x) { patrol_min_x = min_x; patrol_max_x = max_x; }

private:
    float direction = 1.0f;
    int patrol_min_x = 0;
    int patrol_max_x = 800;
};
