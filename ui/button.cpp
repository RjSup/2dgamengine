#include "button.hpp"
#include "SDL_render.h"

Button::Button(SDL_Texture* normal, SDL_Texture* hover, int x, int y, int width, int height)
    : texture(normal), texture_hover(hover)
{
    rect = { x, y, width, height };
}

Button::~Button()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture_hover);
}

void Button::update(const Input_State& input)
{
    // get mouse state
    int mouse_x = input.mouse_x;
    int mouse_y = input.mouse_y;

    // check mosue state is hovering over button
    hovered = (mouse_x >= rect.x && mouse_x <= rect.x + rect.w &&
        mouse_y >= rect.y && mouse_y <= rect.y + rect.h);

    // check if mouse pressed
    bool mouse_down = input.is_mouse_pressed(SDL_BUTTON_LEFT);

    // check click detection and released inside rect
    if(!mouse_down && pressed && hovered) {
        if(on_click) {
            on_click();
        }
    }

    pressed = mouse_down;
}

void Button::render(SDL_Renderer* renderer)
{
    // check which texture to render
    SDL_Texture* button_texture = hovered ? texture_hover : texture;
    // render the button
    SDL_RenderCopy(renderer, button_texture, nullptr, &rect);
}
