#pragma once
#include "SDL_rect.h"
#include <vector>

class Animation {
public:
    Animation(int row, int frame_width, int frame_height, int total_frames, float frame_time);

// update the aniamtion based on delta time
void update(float delta_time);
    // get the current frame of animation
    SDL_Rect get_frame() const { return frames[current_frame]; }
    // reset the animations so init state
    void reset() { current_frame = 0; timer = 0.0f; }

private:
// array of frames
    std::vector<SDL_Rect> frames;
    int frame_width, frame_height;
    float frame_time;

    float timer = 0.0f;
    int current_frame = 0;
};
