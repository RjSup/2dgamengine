#pragma once
#include "scene.hpp"
#include "scene_manager.hpp"
#include "input.hpp"
#include "button.hpp"
#include "background.hpp"
#include <SDL.h>

class MenuScene : public Scene {
public:
    MenuScene(SceneManager* manager, SDL_Renderer* renderer);
    ~MenuScene() override = default;

    void on_enter() override;
    void on_exit() override;
    void update(float deltaTime, const Input_State& input) override;
    void render(SDL_Renderer* renderer, const Camera* cam = nullptr) override;

private:
    SceneManager* manager = nullptr;
    SDL_Renderer* renderer = nullptr;

    Button* start_button = nullptr;
    Button* option_button = nullptr;
    Button* exit_button = nullptr;

    Background* background = nullptr;

    bool started = false;
};
