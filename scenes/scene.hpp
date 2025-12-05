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
    virtual ~Scene() = default;  // virtual destructor

    virtual void on_enter() {}
    virtual void on_exit() {}
    virtual void update(float delta_time, const Input_State& input);
    virtual void render(SDL_Renderer* renderer, const Camera* cam = nullptr);

    void add_object(const std::shared_ptr<Sprite>& obj);
    void remove_object(Sprite* obj);

    void set_debug_mode(bool enabled) { collider.set_debug_mode(enabled); }
    bool is_debug_mode() const { return collider.is_debug_mode(); }

protected:
    std::vector<std::shared_ptr<Sprite>> objects;
    Collider collider;
};
