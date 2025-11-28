#ifndef GAME_H
#define GAME_H

#include <SDL.h>

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool isRunning() const { return running; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
};

#endif // GAME_H
