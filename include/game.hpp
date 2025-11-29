#pragma once

#include <SDL.h>
#include <memory>
#include "window.hpp"
#include "renderer.hpp"
#include "input.hpp"
#include "sprite.hpp"
#include "animation.hpp"

class Game {
    public:
        Game();
        ~Game();

        bool init(const char* title, int width, int height);
        void handleEvents();
        void update(float deltaTime);
        void render();
        void clean();

        bool isRunning() const { return running; }

        const InputState& getInput() const { return input; }

    private:
        // unique data storage
        std::unique_ptr<Window> window;
        std::unique_ptr<Renderer> renderer;

        // player instance
        std::shared_ptr<Sprite> player;

        // animation instances
        std::shared_ptr<Animation> idleAnimation;
        std::shared_ptr<Animation> moveLeftAnimation;
        std::shared_ptr<Animation> moveRightAnimation;
        // std::shared_ptr<Animation> moveUpAnimation;
        // std::shared_ptr<Animation> moveDownAnimation;

        bool running;
        InputState input;
};
