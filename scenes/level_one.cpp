#include "level_one.hpp"

LevelOne::LevelOne(SceneManager* manager_, SDL_Renderer* renderer_, int screen_w, int screen_h)
    : manager(manager_), renderer(renderer_), camera(level_bounds.w, level_bounds.h, 0.1f)
{
    camera.set_screen_size(screen_w, screen_h);
}

void LevelOne::on_enter() {
    spawn_player(renderer);
    spawn_enemies(renderer, 1);
}

void LevelOne::on_exit() {
    objects.clear();
    enemies.clear();
    player.reset();
}

void LevelOne::update(float delta_time, const Input_State& input) {
    if (player) player->handle_input(input, delta_time);

    for (auto& enemy : enemies)
        enemy->update_movement(delta_time, player->get_dest_rect().x, player->get_dest_rect().y);

    Scene::update(delta_time, input);

    if (player)
        camera.follow(player->get_dest_rect(), delta_time);

    // Debug
    // std::cout << "Camera: " << camera.get_x() << ", " << camera.get_y() << "\n";
}

void LevelOne::render(SDL_Renderer* renderer, const Camera* cam) {
    Scene::render(renderer, cam ? cam : &camera);
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
        // x pos for each enemy
        int x = 50 + i * rand() % 1900;
        int y = 50 + i * rand() % 1200;
        auto enemy = std::make_shared<Enemy>(renderer_, "assets/random.png", x, y, 64, 64);
        enemy->add_animation("left", std::make_unique<Animation>(1, 64, 64, 4, 0.15f));
        enemy->add_animation("right", std::make_unique<Animation>(2, 64, 64, 4, 0.15f));
        enemy->set_animation("right");
        // enemy->set_patrol_bounds(100, 1900);
        enemies.push_back(enemy);
        add_object(enemy);
    }
}
