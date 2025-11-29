#include "game.hpp"
#include <SDL.h>
#include <iomanip>
#include <iostream>

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    // fps thigns
    const int TARGET_FPS = 60;
    const int FRAME_DELAY = 1000 / TARGET_FPS;

    // init game instance
    Game game;

    if (!game.init("Endeavor", 800, 600)) {
        return 1;
    }

    // fps and delta time
    Uint32 frameStart;
    int frameTime;
    float deltaTime = 0.0f;
    float fps = 0.0f;

    // Game loop
    while (game.isRunning()) {
        frameStart = SDL_GetTicks();

        // Handle events
        game.handleEvents();

        // Update with deltaTime
        game.update(deltaTime);

        // Render
        game.render();

        // Frame timing
        frameTime = SDL_GetTicks() - frameStart;

        // Limit to target FPS
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
            // recalc frametime after delay
            frameTime = SDL_GetTicks() - frameStart;
        }

        // Compute deltaTime in seconds
        deltaTime = frameTime / 1000.0f;

        // Compute FPS
        fps = (frameTime > 0) ? 1000.0f / frameTime : 0.0f;

        // to 3 decomal places
        std::cout << std::fixed << std::setprecision(3);
        std::cout << "DeltaTime: " << deltaTime << " s | FPS: " << fps << "           \r";
        std::cout.flush();
    }

    std::cout << std::endl;

    game.clean();

    return 0;
}
