#pragma once
#include <vector>
#include <memory>
#include "scene.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "scene_manager.hpp"
#include "camera.hpp"

class LevelOne : public Scene {
public:
    LevelOne(SceneManager* manager, SDL_Renderer* renderer, int screen_w, int screen_h);
    ~LevelOne() override = default;

    void on_enter() override;
    void on_exit() override;
    void update(float delta_time, const Input_State& input) override;
    void render(SDL_Renderer* renderer, const Camera* cam = nullptr) override;

    Camera& get_camera() { return camera; }

private:
    void spawn_player(SDL_Renderer* renderer);
    void spawn_enemies(SDL_Renderer* renderer, int count);

    SceneManager* manager = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Enemy>> enemies;

    SDL_Rect level_bounds = {0, 0, 2000, 1200};

    Camera camera;
};
