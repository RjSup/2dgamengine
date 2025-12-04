#include "game.hpp"
#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "SDL_image.h"
#include <exception>
#include <iostream>

#include "menu_scene.hpp"
#include "level_one.hpp"
#include "scene_manager.hpp"

Game::Game() : running(false) {}
Game::~Game() { clean(); }

bool Game::init(const char* title, int width, int height) {
    std::cout << "Starting SDL initialization..." << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image PNG support not initialized: " << IMG_GetError() << std::endl;
        return false;
    }

    try {
        // init window - renderer - scene manager
        window = std::make_unique<Window>(title, width, height);
        renderer = std::make_unique<Renderer>(*window);
        scene_manager = std::make_unique<SceneManager>();

        // add scenes
        scene_manager->add_scene<MenuScene>("menu", scene_manager.get(), renderer->get());
        scene_manager->add_scene<LevelOne>("level_1", scene_manager.get(), renderer->get());
        // scene_manager->add_scene<Options>("options", scene_manager.get(), renderer->get());

        if (!scene_manager->switch_to_scene("menu")) {
            throw std::runtime_error("Failed to switch to menu");
        }
    } catch (const std::exception& ex) {
        std::cerr << "Init error: " << ex.what() << std::endl;
        return false;
    }

    running = true;
    std::cout << "Game initialized successfully!" << std::endl;
    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                input.keys[event.key.keysym.sym] = Key_State::Pressed;
                if (event.key.keysym.sym == SDLK_ESCAPE) running = false;
                if (event.key.keysym.sym == SDLK_0) {
                    // toggle debug mode on the scene
                    auto current = scene_manager->get_current_scene();
                    if (current) current->set_debug_mode(!current->is_debug_mode());
                }
                break;
            case SDL_KEYUP:
                input.keys[event.key.keysym.sym] = Key_State::Released;
                break;
            case SDL_MOUSEBUTTONDOWN:
                input.mouse_button[event.button.button] = Key_State::Pressed;
                break;
            case SDL_MOUSEBUTTONUP:
                input.mouse_button[event.button.button] = Key_State::Released;
                break;
            case SDL_MOUSEMOTION:
                input.mouse_x = event.motion.x;
                input.mouse_y = event.motion.y;
                break;
            default:
                break;
        }
    }
}

void Game::update(float delta_time) {
    if (scene_manager) scene_manager->update(delta_time, input);
}

void Game::render() {
    renderer->set_draw_color(222, 165, 164);
    renderer->clear();

    if (scene_manager) scene_manager->render(renderer->get());

    renderer->present();
}

void Game::clean() {
    if (scene_manager) scene_manager.reset();
    if (renderer) renderer.reset();
    if (window) window.reset();

    IMG_Quit();
    SDL_Quit();

    std::cout << "Game cleaned up" << std::endl;
}
