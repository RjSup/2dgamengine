#include "collider.hpp"

void Collider::add_sprite(const std::shared_ptr<Sprite>& sprite) {
    if (!sprite) return;
    sprites.emplace_back(sprite);
}

void Collider::remove_sprite(Sprite* sprite) {
    // remove sprites if they match the capture group
    sprites.erase(std::remove_if(sprites.begin(), sprites.end(),
        [&](const std::weak_ptr<Sprite>& w) {
            auto s = w.lock();
            return !s || s.get() == sprite;
        }), sprites.end());
}

bool Collider::check_collision(const SDL_Rect& a, const SDL_Rect& b) {
    return !(a.x + a.w <= b.x || a.x >= b.x + b.w ||
             a.y + a.h <= b.y || a.y >= b.y + b.h);
}

void Collider::update() {
    // lock all weak_ptrs as itterationis done
    for (auto& ws : sprites) {
        auto s = ws.lock();
        if (!s) continue;
        SDL_Rect box = s->get_collision_box();
        bool colliding = false;

        for (auto& ws2 : sprites) {
            auto o = ws2.lock();
            if (!o || o.get() == s.get()) continue;
            // check for collisions with items and sprites
            if (check_collision(box, o->get_collision_box())) {
                colliding = true;
                break;
            }
        }

        // colliding true and debug true
        s->set_colliding(colliding);
        s->set_debug_box(debug_mode);
    }
}
