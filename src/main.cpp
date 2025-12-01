#include "game.hpp"
#include <SDL.h>
#include <iostream>
#include <iomanip>

int main(int argc, char* argv[]) {
    (void)argc; (void)argv;

    Game game;
    if (!game.init("Endeavor", 800, 600)) {
        std::cerr << "Failed to initialize game" << std::endl;
        return 1;
    }

    const int target_fps = 60;
    const int frame_delay = 1000 / target_fps;

    Uint32 frame_start;
    int frame_time;
    float delta_time = 0.0f;
    float fps = 0.0f;

    while (game.is_running()) {
        frame_start = SDL_GetTicks();

        game.handleEvents();
        game.update(delta_time);
        game.render();

        frame_time = SDL_GetTicks() - frame_start;

        if (frame_time < frame_delay) {
            SDL_Delay(frame_delay - frame_time);
            frame_time = SDL_GetTicks() - frame_start;
        }

        delta_time = frame_time / 1000.0f;
        fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;

        std::cout << std::fixed << std::setprecision(3);
        std::cout << "DeltaTime: " << delta_time << " s | FPS: " << fps << "           \r";
        std::cout.flush();
    }

    std::cout << std::endl;
    return 0;
}
