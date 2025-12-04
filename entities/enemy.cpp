#include "enemy.hpp"

Enemy::Enemy(SDL_Renderer* renderer, const std::string& path, int x, int y, int width, int height)
    : Sprite(renderer, path, x, y, width, height) {}

void Enemy::update_movement(float delta_time) {
    const float speed = 100.0f;
    int new_x = getX() + static_cast<int>(direction * speed * delta_time);
    // go right
    if (new_x < patrol_min_x) {
        new_x = patrol_min_x;
        direction = 1.0f;
        // go left
    } else if (new_x > patrol_max_x - 1) {
        new_x = patrol_max_x - 1;
        direction = -1.0f;
    }

    set_position(new_x, getY());
    // set anim to either left or right
    set_animation(direction < 0 ? "left" : "right");
}
