#include "camera.hpp"

Camera::Camera(int level_width, int level_height, float smooth_factor)
    : x(0), y(0), w(800), h(600),
      level_w(level_width), level_h(level_height),
      smooth(smooth_factor) {}

void Camera::set_screen_size(int screen_width, int screen_height) {
    w = screen_width;
    h = screen_height;
}

void Camera::follow(const SDL_Rect& target, float delta_time) {
    if (delta_time <= 0.0f) delta_time = 0.016f;

    float target_x = static_cast<float>(target.x + target.w / 2 - w / 2);
    float target_y = static_cast<float>(target.y + target.h / 2 - h / 2);

    x += (target_x - x) * smooth;
    y += (target_y - y) * smooth;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > level_w - w) x = static_cast<float>(level_w - w);
    if (y > level_h - h) y = static_cast<float>(level_h - h);
}
