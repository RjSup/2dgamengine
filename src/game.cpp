#include "game.hpp"
#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "SDL_image.h"
#include "input.hpp"
#include "sprite.hpp"
#include "animation.hpp"
#include "collider.hpp"
#include <exception>
#include <iostream>
#include <memory>
#include <cmath>

Game::Game() : running(false) {}

Game::~Game() {
    clean();
}

bool Game::init(const char* title, int width, int height) {
    std::cout << "Starting SDL initialization..." << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    int initted = IMG_Init(imgFlags);
    std::cout << "IMG_Init returned: " << initted << std::endl;
    if (!(initted & IMG_INIT_PNG)) {
        std::cerr << "SDL_image PNG support not initialized: " << IMG_GetError() << std::endl;
        return false;
    }

    try {
        // Window
        window = std::make_unique<Window>(title, width, height);
        if (!window) throw std::runtime_error("Failed to create window");

        // Renderer
        renderer = std::make_unique<Renderer>(*window);
        if (!renderer || !renderer->get()) throw std::runtime_error("Failed to create renderer");

        // Player sprite
        player = std::make_unique<Sprite>(renderer->get(), "assets/random.png", 100, 100, 64, 64);

        // Animations (Game owns them)
        idleAnimation = std::make_unique<Animation>(0, 64, 64, 4, 0.15f);
        moveLeftAnimation = std::make_unique<Animation>(1, 64, 64, 4, 0.15f);
        moveRightAnimation = std::make_unique<Animation>(2, 64, 64, 4, 0.15f);

        // Initial animation
        player->setAnimation(idleAnimation.get());

        // Enemies
        enemies.push_back(std::make_unique<Sprite>(renderer->get(), "assets/random.png", 100, 100, 64, 64));
        enemies.push_back(std::make_unique<Sprite>(renderer->get(), "assets/random.png", 200, 200, 64, 64));
        enemies.push_back(std::make_unique<Sprite>(renderer->get(), "assets/random.png", 300, 200, 64, 64));
        enemies.push_back(std::make_unique<Sprite>(renderer->get(), "assets/random.png", 400, 400, 64, 64));

        // Add collider (non-owning pointers)
        collider.addSprite(player.get());
        for (auto& e : enemies) {
            collider.addSprite(e.get());
        }

    } catch (const std::exception& e) {
        std::cerr << "Init error: " << e.what() << std::endl;
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
            case SDL_QUIT: running = false; break;
            case SDL_KEYDOWN:
                input.keys[event.key.keysym.sym] = KeyState::Pressed;
                if(event.key.keysym.sym == SDLK_ESCAPE) running = false;
                if(event.key.keysym.sym == SDLK_0) collider.setDebugMode(true);
                break;
            case SDL_KEYUP:
                input.keys[event.key.keysym.sym] = KeyState::Released;
                break;
            case SDL_MOUSEBUTTONDOWN:
                input.mouseButtons[event.button.button] = KeyState::Pressed;
                break;
            case SDL_MOUSEBUTTONUP:
                input.mouseButtons[event.button.button] = KeyState::Released;
                break;
        }
    }
}

void Game::update(float deltaTime) {
    const float speed = 200.0f;
    float moveX = 0.0f, moveY = 0.0f;

    if (input.isKeyPressed(SDLK_w) || input.isKeyPressed(SDLK_UP)) moveY -= 1.0f;
    if (input.isKeyPressed(SDLK_s) || input.isKeyPressed(SDLK_DOWN)) moveY += 1.0f;
    if (input.isKeyPressed(SDLK_a) || input.isKeyPressed(SDLK_LEFT)) moveX -= 1.0f;
    if (input.isKeyPressed(SDLK_d) || input.isKeyPressed(SDLK_RIGHT)) moveX += 1.0f;

    // Normalize diagonal movement
    if (moveX != 0.0f || moveY != 0.0f) {
        float length = std::sqrt(moveX * moveX + moveY * moveY);
        moveX /= length;
        moveY /= length;
    }

    int newX = player->getX() + static_cast<int>(moveX * speed * deltaTime);
    int newY = player->getY() + static_cast<int>(moveY * speed * deltaTime);
    player->setPosition(newX, newY);

    // Set animation
    if (moveX < 0) player->setAnimation(moveLeftAnimation.get());
    else if (moveX > 0) player->setAnimation(moveRightAnimation.get());
    else player->setAnimation(idleAnimation.get());

    player->update(deltaTime);
    for (auto& e : enemies) e->update(deltaTime);

    // Collider updates
    collider.update();
}

void Game::render() {
    renderer->setDrawColor(222, 165, 164);
    renderer->clear();

    player->render(renderer->get());
    for (auto& e : enemies) e->render(renderer->get());

    renderer->present();
}

void Game::clean() {
    // Clear owned objects
    player.reset();
    for (auto& e : enemies) e.reset();
    enemies.clear();

    renderer.reset();
    window.reset();

    IMG_Quit();
    SDL_Quit();

    std::cout << "Game cleaned up" << std::endl;
}
