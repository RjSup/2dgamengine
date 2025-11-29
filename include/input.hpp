#pragma once

#include <SDL.h>
#include <unordered_map>

enum class KeyState { Pressed, Released };

struct InputState {
    std::unordered_map<SDL_Keycode, KeyState> keys; // keyboard states
    int mouseX = 0; // mouse x pos
    int mouseY = 0; // mouse y pos
    std::unordered_map<Uint8, KeyState> mouseButtons;   // mouse buttons

    // are keys pressed
    bool isKeyPressed(SDL_Keycode key) const {
        // find the key pressed
        auto it = keys.find(key);
        // return that key didnt end and its state is pressed
        return it != keys.end() && it->second == KeyState::Pressed;
    }

    bool isKeyReleased(SDL_Keycode key) const {
        // find the key realsed
        auto it = keys.find(key);
        // change its state to released
        return it != keys.end() && it->second == KeyState::Released;
    }

    // is mouse pressed
    bool isMousePressed(Uint8 button) const {
        // find the mouse button
        auto it = mouseButtons.find(button);
        // return state is pressed
        return it != mouseButtons.end() && it->second == KeyState::Pressed;
    }

    bool isMouseRelease(Uint8 button) const {
        auto it = mouseButtons.find(button);
        return it != mouseButtons.end() && it->second == KeyState::Released;
    }
};
