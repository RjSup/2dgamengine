#include "menu_scene.hpp"
#include "SDL_events.h"
#include "SDL_render.h"
#include <SDL.h>
#include <SDL_image.h>

MenuScene::MenuScene(SceneManager* manager, SDL_Renderer* renderer)
    : manager(manager), renderer(renderer) {}

// Called when this scene is entered
void MenuScene::on_enter() {
    started = true;

    // textures for button state
    SDL_Texture* start_button_normal = IMG_LoadTexture(renderer, "assets/start.png");
    SDL_Texture* start_button_hover = IMG_LoadTexture(renderer, "assets/start_hover.png");
    SDL_Texture* option_button_normal = IMG_LoadTexture(renderer, "assets/options.png");
    SDL_Texture* option_button_hover = IMG_LoadTexture(renderer, "assets/option_hover.png");
    SDL_Texture* exit_button_normal = IMG_LoadTexture(renderer, "assets/exit.png");
    SDL_Texture* exit_button_hover = IMG_LoadTexture(renderer, "assets/exit_hover.png");

    // create button
    start_button = new Button(start_button_normal, start_button_hover, 300, 200, 200, 80);
    option_button = new Button(option_button_normal, option_button_hover, 300, 300, 200, 80);
    exit_button = new Button(exit_button_normal, exit_button_hover, 300, 400, 200, 80);

    // on click - should go to level1
    start_button->set_on_click([this]() {
        manager->switch_to_scene("level_1");
    });

    // on click shoudl go to options
    option_button->set_on_click([this]() {
        manager->switch_to_scene("options");
    });

    exit_button->set_on_click([]() {
        SDL_Event quit_event;
        quit_event.type = SDL_QUIT;
        SDL_PushEvent(&quit_event);
    });
}

void MenuScene::on_exit() {
    // clean all objects
    objects.clear();
    delete start_button;
    delete option_button;
    delete exit_button;
}

// handles input and updates menu logic
void MenuScene::update(float deltaTime, const Input_State& input) {
    if (!started) return;

    // give onhover effect to show hovered style button
    start_button->update(input);
    option_button->update(input);
    exit_button->update(input);

    // if enter pressed go to game
    // if (input.is_key_pressed(SDLK_RETURN)) {
    //     // Switch to game
    //     if (manager) {
    //         manager->switch_to_scene("level_1");
    //     }
    // }

    // if esc go to menu

}

// draw the menu
void MenuScene::render(SDL_Renderer* renderer) {
    start_button->render(renderer);
    option_button->render(renderer);
    exit_button->render(renderer);
}
