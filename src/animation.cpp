#include "animation.hpp"

Animation::Animation(int row, int frameW, int frameH, int totalFrames, float frameTime)
    : frameW(frameW), frameH(frameH), frameTime(frameTime)
{
    frames.reserve(totalFrames);
    for (int i = 0; i < totalFrames; ++i) {
        frames.emplace_back(SDL_Rect{i * frameW, row * frameH, frameW, frameH});
    }
}



void Animation::update(float deltaTime) {
    // init timer as delta time
    timer += deltaTime;

    // if timer has run its time
    if (timer >= frameTime) {
        // reset time
        timer -= frameTime;

        // advance the frame index for size frames
        currentFrame = (currentFrame + 1) % frames.size();
    }
}
