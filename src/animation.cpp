#include "animation.hpp"

Animation::Animation(int row, int frame_w, int frame_h, int total_frames, float frame_time)
    : frame_width(frame_w), frame_height(frame_h), frame_time(frame_time)
{
    // locate all frames from sprite sheet [][][][]
    frames.reserve(total_frames);
    for (int i = 0; i < total_frames; ++i) {
        frames.emplace_back(SDL_Rect{ i * frame_w, row * frame_h, frame_w, frame_h });
    }
}

void Animation::update(float delta_time) {
    // ensuring aniamtion updates are using delta time
    timer += delta_time;
    // when time gone past = frametime which is how many frames available
    if (timer >= frame_time) {
        // reset timer - basically replay the anim
        timer -= frame_time;
        // advance through the frames
        current_frame = (current_frame + 1) % static_cast<int>(frames.size());
    }
}
