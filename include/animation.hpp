#pragma once

#include "SDL_rect.h"

#include <vector>

class Animation {
    public:
        // animation must be 32x32 area of a sprite sheet
        Animation(int row, int frameW, int frameH, int totalFrames, float frameTime);

        // update the location of spritesheet over time
        void update(float deltaTime);

        // what frame of the animation are we at
        SDL_Rect getFrame() const { return frames[currentFrame]; };

        void reset() { currentFrame = 0; timer = 0.0f; }

    private:
        // store each frame of the sheet to loop them
        std::vector<SDL_Rect> frames;
        int frameW, frameH;
        float frameTime;

        float timer = 0.0f;
        int currentFrame = 0;
};
