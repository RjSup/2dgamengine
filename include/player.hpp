#pragma once
#include "sprite.hpp"
#include "input.hpp"

class Player : public Sprite {
public:
    Player(SDL_Renderer* renderer, const std::string& path, int x, int y, int width, int height);
    // all player sprite input handling
    void handle_input(const Input_State& input, float delta_time);
};
