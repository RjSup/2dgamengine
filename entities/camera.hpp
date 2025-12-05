#pragma once
#include <SDL.h>

class Camera {
public:
    Camera(int level_width, int level_height, float smooth_factor = 0.1f);

    void set_screen_size(int screen_width, int screen_height);
    void follow(const SDL_Rect& target, float delta_time);

    int get_x() const { return static_cast<int>(x); }
    int get_y() const { return static_cast<int>(y); }
    int get_w() const { return w; }
    int get_h() const { return h; }

private:
    float x, y;
    int w, h;
    int level_w, level_h;
    float smooth;
};
