#include "menu_scene.hpp"
#include <SDL.h>

MenuScene::MenuScene(SceneManager* manager, SDL_Renderer* renderer)
    : manager(manager), renderer(renderer), started(false) {}

// Called when this scene is entered
void MenuScene::on_enter() {
    started = true;
}

// handles input and updates menu logic
void MenuScene::update(float deltaTime, const Input_State& input) {
    if (!started) return;

    // if enter pressed go to game - TODO
    if (input.is_key_pressed(SDLK_RETURN)) {
        // Switch to game
        if (manager) {
            manager->switch_to_scene("level_1");
        }
    }

}

// Render function: draws the menu
void MenuScene::render(SDL_Renderer* renderer) {

}
