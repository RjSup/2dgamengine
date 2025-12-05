#include "menu_scene.hpp"
#include "SDL_image.h"
#include <SDL.h>

MenuScene::MenuScene(SceneManager* manager_, SDL_Renderer* renderer_)
    : manager(manager_), renderer(renderer_) {}

void MenuScene::on_enter() {
    started = true;

    SDL_Texture* start_normal = IMG_LoadTexture(renderer, "assets/start.png");
    SDL_Texture* start_hover = IMG_LoadTexture(renderer, "assets/start_hover.png");
    SDL_Texture* option_normal = IMG_LoadTexture(renderer, "assets/options.png");
    SDL_Texture* option_hover = IMG_LoadTexture(renderer, "assets/option_hover.png");
    SDL_Texture* exit_normal = IMG_LoadTexture(renderer, "assets/exit.png");
    SDL_Texture* exit_hover = IMG_LoadTexture(renderer, "assets/exit_hover.png");

    SDL_Texture* background_img = IMG_LoadTexture(renderer, "assets/background.png");

    start_button = new Button(start_normal, start_hover, 300, 200, 200, 80);
    option_button = new Button(option_normal, option_hover, 300, 300, 200, 80);
    exit_button = new Button(exit_normal, exit_hover, 300, 400, 200, 80);

    background = new Background(background_img, 800, 600);

    start_button->set_on_click([this]() { manager->switch_to_scene("level_1"); });
    option_button->set_on_click([this]() { manager->switch_to_scene("options"); });
    exit_button->set_on_click([]() {
        SDL_Event quit_event;
        quit_event.type = SDL_QUIT;
        SDL_PushEvent(&quit_event);
    });
}

void MenuScene::on_exit() {
    objects.clear();
    delete start_button;
    delete option_button;
    delete exit_button;
    delete background;
}

void MenuScene::update(float deltaTime, const Input_State& input) {
    if (!started) return;
    start_button->update(input);
    option_button->update(input);
    exit_button->update(input);
}

void MenuScene::render(SDL_Renderer* renderer, const Camera* cam) {
    background->render(renderer);
    start_button->render(renderer);
    option_button->render(renderer);
    exit_button->render(renderer);
}
