#include "level_one.hpp"
#include "SDL_render.h"
#include "input.hpp"

LevelOne::LevelOne(SceneManager* manager_, SDL_Renderer* renderer_)
    : manager(manager_), renderer(renderer_) {}

void LevelOne::on_enter() {
    // spwan player and enemy when scene enters
    spawn_player(renderer);
    spawn_enemies(renderer, 3);
}

void LevelOne::on_exit() {
    // clean all objects
    objects.clear();
    enemies.clear();
    player.reset();
}

void LevelOne::update(float delta_time, const Input_State& input) {
    // player input
    if (player) {
        player->handle_input(input, delta_time);
    }

    // enemy movement
    for (auto& enemy : enemies) {
        enemy->update_movement(delta_time);
    }

    // animations and collider checks
    Scene::update(delta_time, input);
}

void LevelOne::render(SDL_Renderer* renderer) {
    Scene::render(renderer);
}

void LevelOne::spawn_player(SDL_Renderer* renderer_) {
    auto p1 = std::make_shared<Player>(renderer_, "assets/random.png", 100, 100, 64, 64);
    p1->add_animation("idle", std::make_unique<Animation>(0, 64, 64, 4, 0.15f));
    p1->add_animation("left", std::make_unique<Animation>(1, 64, 64, 4, 0.15f));
    p1->add_animation("right", std::make_unique<Animation>(2, 64, 64, 4, 0.15f));
    p1->set_animation("idle");

    player = p1;
    add_object(p1);
}

void LevelOne::spawn_enemies(SDL_Renderer* renderer_, int count) {
    for (int i = 0; i < count; ++i) {
        int x = 200 + i * 120;
        int y = 200;
        auto enemy = std::make_shared<Enemy>(renderer_, "assets/random.png", x, y, 64, 64);
        // assign animations
        enemy->add_animation("left", std::make_unique<Animation>(1, 64, 64, 4, 0.15f));
        enemy->add_animation("right", std::make_unique<Animation>(2, 64, 64, 4, 0.15f));
        enemy->set_animation("right");

        // set patrol bounds
        enemy->set_patrol_bounds(100, 700);

        enemies.push_back(enemy);

        add_object(enemy);
    }
}
