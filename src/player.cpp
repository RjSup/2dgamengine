#include "player.hpp"
#include <cmath>

Player::Player(SDL_Renderer* renderer, const std::string& path, int x, int y, int width, int height)
    : Sprite(renderer, path, x, y, width, height) {}

void Player::handle_input(const Input_State& input, float delta_time) {
    const float speed = 200.0f;
    float move_x = 0.0f, move_y = 0.0f;

    if (input.is_key_pressed(SDLK_w) || input.is_key_pressed(SDLK_UP)) move_y -= 1.0f;
    if (input.is_key_pressed(SDLK_s) || input.is_key_pressed(SDLK_DOWN)) move_y += 1.0f;
    if (input.is_key_pressed(SDLK_a) || input.is_key_pressed(SDLK_LEFT)) move_x -= 1.0f;
    if (input.is_key_pressed(SDLK_d) || input.is_key_pressed(SDLK_RIGHT)) move_x += 1.0f;

    // normalize
    if (move_x != 0.0f || move_y != 0.0f) {
        float len = std::sqrt(move_x * move_x + move_y * move_y);
        move_x /= len;
        move_y /= len;
    }

    set_position(getX() + static_cast<int>(move_x * speed * delta_time),
                getY() + static_cast<int>(move_y * speed * delta_time));

    if (move_x < 0) set_animation("left");
    else if (move_x > 0) set_animation("right");
    else set_animation("idle");
}
