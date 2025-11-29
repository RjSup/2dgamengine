#include "game.hpp"
#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "SDL_image.h"
#include "input.hpp"
#include "sprite.hpp"
#include "animation.hpp"
#include <exception>
#include <iostream>
#include <memory>

Game::Game() : window(nullptr), renderer(nullptr), running(false) {}

Game::~Game() {
    clean();
}

bool Game::init(const char* title, int width, int height) {
    std::cout << "Starting SDL initialization..." << std::endl;

    // init sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    //  init img for png
    int imgFlags = IMG_INIT_PNG;
    int initted = IMG_Init(imgFlags);
    std::cout << "IMG_Init returned: " << initted << std::endl;
    if (!(initted & IMG_INIT_PNG)) {
        std::cerr << "SDL_image PNG support not initialized: " << IMG_GetError() << std::endl;
        return false;
    }

    try {
        // make window
        window = std::make_unique<Window>(title, width, height);
        if (!window) throw std::runtime_error("Failed to create window");

        // make renderer
        renderer = std::make_unique<Renderer>(*window);
        if (!renderer || !renderer->get()) throw std::runtime_error("Failed to create renderer");

        // make sprite w texture
        player = std::make_shared<Sprite>(renderer->get(), "assets/random.png", 100, 100, 64, 64);

        // aniamtions
        idleAnimation = std::make_shared<Animation>(0, 64, 64, 4, 0.15f);
        moveLeftAnimation = std::make_shared<Animation>(1, 64, 64, 4, 0.15f);
        moveRightAnimation = std::make_shared<Animation>(2, 64, 64, 4, 0.15f);
        // moveUpAnimation = std::make_shared<Animation>(3, 64, 64, 4, 0.15f);
        // moveDownAnimation = std::make_shared<Animation>(4, 64, 64, 4, 0.15f);

        // set initial anim to idle
        player->setAnimation(idleAnimation);

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
            // if quit pressed
            case SDL_QUIT:
                running = false;
                break;

            // if key pressed
            case SDL_KEYDOWN:
            // get the key
                input.keys[event.key.keysym.sym] = KeyState::Pressed;

                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }

                // std::cout << "Key pressed: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
                break;

            // if key released
            case SDL_KEYUP:
            // get the key
                // std::cout << "Key released: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
                input.keys[event.key.keysym.sym] = KeyState::Released;
                break;

            // if button pressed
            case SDL_MOUSEBUTTONDOWN:
                input.mouseButtons[event.button.button] = KeyState::Pressed;
                // std::cout << "Mouse button pressed" << std::endl;
                break;

            case SDL_MOUSEBUTTONUP:
                input.mouseButtons[event.button.button] = KeyState::Released;
                // std::cout << "Mouse button release" << std::endl;
                break;
        }
    }
}

void Game::update(float deltaTime) {
    // speed of sprite
    const float speed = 200.0f;
    float moveX = 0.0f;
    float moveY = 0.0f;

    // w - up
    if (input.isKeyPressed(SDLK_w) || input.isKeyPressed(SDLK_UP)) {
        moveY -= 1.0f;
    }
    // s - down
    if (input.isKeyPressed(SDLK_s) || input.isKeyPressed(SDLK_DOWN)) {
        moveY += 1.0f;
    }
    // a - left
    if (input.isKeyPressed(SDLK_a) || input.isKeyPressed(SDLK_LEFT)) {
        moveX -= 1.0f;
    }
    // d - right
    if (input.isKeyPressed(SDLK_d) || input.isKeyPressed(SDLK_RIGHT)) {
        moveX += 1.0f;
    }

    // Normalize diagonal movement
    if (moveX != 0.0f || moveY != 0.0f) {
        float length = sqrt(moveX * moveX + moveY * moveY);
        moveX /= length;
        moveY /= length;
    }

    // Apply movement
    int newX = player->getX() + static_cast<int>(moveX * speed * deltaTime);
    int newY = player->getY() + static_cast<int>(moveY * speed * deltaTime);
    player->setPosition(newX, newY);

    // set aniamtions
    if (moveX < 0) {
        player->setAnimation(moveLeftAnimation);
    }
    else if (moveX > 0) {
        player->setAnimation(moveRightAnimation);
    }
    // else if (moveY < 0) {
    //     player->setAnimation(moveUpAnimation);
    // }
    // else if (moveY > 0) {
    //     player->setAnimation(moveDownAnimation);
    // }
    else {
        player->setAnimation(idleAnimation);
    }

    player->update(deltaTime);
}


void Game::render() {
    // Clear screen with blue color
    renderer->setDrawColor(222, 165, 164);
    renderer->clear();

    // render the player sprite
    player->render(renderer->get());

    // Present renderer
    renderer->present();
}

void Game::clean() {
    // clean and deinit all things holding memory
    player.reset();

    renderer.reset();
    window.reset();

    IMG_Quit();
    SDL_Quit();
    std::cout << "Game cleaned up" << std::endl;
}
