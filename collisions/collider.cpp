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

void Collider::collision_resolution(Sprite* sprite1, Sprite* sprite2) {
    SDL_Rect rect_a = sprite1->get_collision_box();
    SDL_Rect rect_b = sprite2->get_collision_box();

    // check overlaps
    int overlap_left = (rect_b.x + rect_b.w) - rect_a.x;
    int overlap_right = (rect_a.x + rect_a.w) - rect_b.x;
    int overlap_top = (rect_b.y + rect_b.h) - rect_a.y;
    int overlap_botton = (rect_a.y + rect_a.h) - rect_b.y;

    // choose minimal penetrations axis
    int move_x = (abs(overlap_left) < abs(overlap_right)) ? overlap_left : -overlap_right;
    int move_y = (abs(overlap_top) < abs(overlap_botton)) ? overlap_top : -overlap_botton;

    if(abs(move_x) < abs(move_y)) {
        move_x /= 2;
        sprite1->set_position(sprite1->getX() + move_x, sprite1->getY());
        sprite2->set_position(sprite2->getX() - move_x, sprite2->getY());
    } else {
        move_y /= 2;
        sprite1->set_position(sprite1->getX(), sprite1->getY() + move_y);
        sprite2->set_position(sprite2->getX(), sprite2->getY() - move_y);
    }

}

void Collider::update() {
    // Lock weak_ptrs into shared_ptrs
    std::vector<std::shared_ptr<Sprite>> active_sprites;
    for (auto& ws : sprites) {
        if (auto s = ws.lock()) {
            active_sprites.push_back(s);
            // reset colliding flag for this frame
            s->set_colliding(false);
            s->set_debug_box(debug_mode);
        }
    }

    // Iterate all unique sprite pairs
    for (size_t i = 0; i < active_sprites.size(); ++i) {
        auto& a = active_sprites[i];
        SDL_Rect box_a = a->get_collision_box();

        for (size_t j = i + 1; j < active_sprites.size(); ++j) {
            auto& b = active_sprites[j];
            SDL_Rect box_b = b->get_collision_box();

            // Check collision
            if (check_collision(box_a, box_b)) {
                // Resolve collision (split overlap)
                collision_resolution(a.get(), b.get());

                // Mark both as colliding
                a->set_colliding(true);
                b->set_colliding(true);

                // Update boxes after resolution
                box_a = a->get_collision_box();
                box_b = b->get_collision_box();
            }
        }
    }
}
