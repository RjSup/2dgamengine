#pragma once
#include "scene.hpp"
#include "scene_manager.hpp"
#include "input.hpp"
#include <SDL.h>

class MenuScene : public Scene {
public:
    MenuScene(SceneManager* manager, SDL_Renderer* renderer);
    virtual ~MenuScene() = default;

    void on_enter() override;
    void update(float deltaTime, const Input_State& input) override;
    void render(SDL_Renderer* renderer) override;

private:
    SceneManager* manager = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool started = false;
};
