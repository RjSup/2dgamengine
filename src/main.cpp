#include "game.h"
#include <SDL.h>

int main(int argc, char* argv[]) {
    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS;

    Game game;

    if (!game.init("SDL Game", 800, 600)) {
        return 1;
    }

    Uint32 frameStart;
    int frameTime;

    // Game loop
    while (game.isRunning()) {
        frameStart = SDL_GetTicks();

        game.handleEvents();
        game.update();
        game.render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 0;
}
