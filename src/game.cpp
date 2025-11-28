#include "game.h"
#include <iostream>

Game::Game() : window(nullptr), renderer(nullptr), running(false) {}

Game::~Game() {
    clean();
}

bool Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    running = true;
    std::cout << "Game initialized successfully!" << std::endl;
    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            running = false;
        }
    }
}

void Game::update() {
    // Game logic updates here
}

void Game::render() {
    // Clear screen with blue color
    SDL_SetRenderDrawColor(renderer, 0, 100, 200, 255);
    SDL_RenderClear(renderer);

    // Draw a red rectangle
    SDL_Rect rect = {300, 200, 200, 200};
    SDL_SetRenderDrawColor(renderer, 222, 165, 164, 255);
    SDL_RenderFillRect(renderer, &rect);

    // Present renderer
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
    std::cout << "Game cleaned up" << std::endl;
}
