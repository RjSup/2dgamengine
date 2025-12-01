#pragma once
#include <vector>
#include <memory>
#include "input.hpp"
#include "sprite.hpp"
#include "collider.hpp"
#include <SDL.h>

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    virtual void on_enter() {}
    virtual void on_exit() {}

    // scene takes ownership with shared_ptr
    void add_object(const std::shared_ptr<Sprite>& obj);
    void remove_object(Sprite* obj);

    virtual void update(float delta_time, const Input_State& input);
    virtual void render(SDL_Renderer* renderer);

    void set_debug_mode(bool enabled) { collider.set_debug_mode(enabled); }
    bool is_debug_mode() const { return collider.is_debug_mode(); }

protected:
    // scene owns all objects
    std::vector<std::shared_ptr<Sprite>> objects;
    // scene handles the collider with objects
    Collider collider;
};
