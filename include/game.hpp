#pragma once
#include <SDL.h>
#include <memory>
#include "window.hpp"
#include "renderer.hpp"
#include "input.hpp"
#include "scene_manager.hpp"


class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height);
    void handleEvents();
    void update(float delta_time);
    void render();
    void clean();

    bool is_running() const { return running; }

private:
    // ownership of data for game
    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<SceneManager> scene_manager;

    Input_State input;
    bool running = false;
};
