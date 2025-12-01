#pragma once
#include "SDL_render.h"
#include "input.hpp"
#include "scene.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "scene_manager.hpp"

class LevelOne : public Scene {
public:
    LevelOne(SceneManager* manager, SDL_Renderer* renderer);
    virtual ~LevelOne() = default;

    void on_enter() override;
    void on_exit() override;

    // update receives input from Game
    void update(float deltaTime, const Input_State& input) override;
    void render(SDL_Renderer* renderer) override;

private:
    void spawn_player(SDL_Renderer* renderer);
    void spawn_enemies(SDL_Renderer* renderer, int count);

    SceneManager* manager = nullptr;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Enemy>> enemies;
    SDL_Renderer* renderer = nullptr;
};
