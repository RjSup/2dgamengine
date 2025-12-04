#pragma once
#include <SDL.h>
#include <functional>

#include "input.hpp"


class Button {
public:
    Button(SDL_Texture* normal, SDL_Texture* hover, int x, int y, int width, int height);
    ~Button();

    void update(const Input_State& input);

    void render(SDL_Renderer* renderer);

    void set_on_click(std::function<void()> func) { on_click = func; };

private:
    SDL_Texture* texture = nullptr;
    SDL_Texture* texture_hover = nullptr;

    SDL_Rect rect;

    bool hovered = false;
    bool pressed = false;

    std::function<void()> on_click;

};
