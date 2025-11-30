#pragma once

#include <SDL.h>
#include <memory>
#include <vector>
#include "window.hpp"
#include "renderer.hpp"
#include "input.hpp"
#include "sprite.hpp"
#include "animation.hpp"
#include "collider.hpp"

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

        // player instance - Game is sole owner
        std::unique_ptr<Sprite> player;
        std::vector<std::unique_ptr<Sprite>> enemies;

        // animation instances - owned by Game; sprites will hold non-owning pointers to these
        std::unique_ptr<Animation> idleAnimation;
        std::unique_ptr<Animation> moveLeftAnimation;
        std::unique_ptr<Animation> moveRightAnimation;
        // std::unique_ptr<Animation> moveUpAnimation;
        // std::unique_ptr<Animation> moveDownAnimation;

        // add collider instance (will store non-owning Sprite* pointers)
        Collider collider;

        bool running;
        InputState input;
};
