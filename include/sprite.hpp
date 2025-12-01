#pragma once
#include <SDL.h>
#include <memory>
#include <string>
#include <unordered_map>
#include "animation.hpp"

class Sprite {
public:
    Sprite(SDL_Renderer* renderer, const std::string& texture_path, int x, int y, int width, int height);
    virtual ~Sprite() = default;

    // sprites are updated based on deltaTime - movement - animations etc
    virtual void update(float delta_time);
    virtual void render(SDL_Renderer* renderer) const;

    void set_position(int x, int y);
    void set_size(int w, int h);
    int getX() const { return destination_rect.x; }
    int getY() const { return destination_rect.y; }

    // loc of collision box on a sprite
    SDL_Rect get_collision_box() const { return { destination_rect.x, destination_rect.y, destination_rect.w, destination_rect.h }; }

    // sprite owns animations
    void add_animation(const std::string& name, std::unique_ptr<Animation> anim);
    void set_animation(const std::string& name);

    void set_debug_box(bool show) { show_debug_box = show; }
    void set_colliding(bool c) { colliding = c; }

protected:
    SDL_Rect destination_rect;
    SDL_Rect source_rect;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture{ nullptr, SDL_DestroyTexture };

private:
    // store all possible animations
    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;
    // pointer to which animation is currently used - init to nullptr
    Animation* current_animation = nullptr;

    float scale_x = 1.0f;
    float scale_y = 1.0f;

    bool show_debug_box = false;
    bool colliding = false;
};
