#pragma once
#include <SDL.h>
#include <unordered_map>

enum class Key_State { Pressed, Released };

struct Input_State {
    // key value storage of key codes and key state
    std::unordered_map<SDL_Keycode, Key_State> keys;
    // same for buttons
    std::unordered_map<Uint8, Key_State> mouse_button;
    int mouse_x = 0, mouse_y = 0;

    bool is_key_pressed(SDL_Keycode key) const {
        // if key pressed find which one
        auto it = keys.find(key);
        // reutrn the key and set state presses
        return it != keys.end() && it->second == Key_State::Pressed;
    }
    bool is_key_released(SDL_Keycode key) const {
        // if key released find which one
        auto it = keys.find(key);
        // return the key and set state to released
        return it != keys.end() && it->second == Key_State::Released;
    }
    bool is_mouse_pressed(Uint8 b) const {
        auto it = mouse_button.find(b);
        return it != mouse_button.end() && it->second == Key_State::Pressed;
    }
};
