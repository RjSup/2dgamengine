#include "sprite.hpp"
#include <SDL_image.h>
#include <stdexcept>

Sprite::Sprite(SDL_Renderer* renderer, const std::string& path, int x, int y, int width, int height)
    : destination_rect{x, y, width, height}, source_rect{0, 0, width, height}, texture(nullptr, SDL_DestroyTexture)
{
    if (!renderer) throw std::runtime_error("Renderer is null in Sprite constructor");

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) throw std::runtime_error("IMG_Load failed for " + path);

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!tex) throw std::runtime_error("SDL_CreateTextureFromSurface failed for " + path);

    texture.reset(tex);
}

void Sprite::add_animation(const std::string& name, std::unique_ptr<Animation> anim) {
    animations[name] = std::move(anim);
}

void Sprite::set_animation(const std::string& name) {
    if (animations.find(name) != animations.end()) {
        current_animation = animations[name].get();
        source_rect = current_animation->get_frame();
    }
}

void Sprite::update(float delta_time) {
    if (current_animation) {
        current_animation->update(delta_time);
        source_rect = current_animation->get_frame();
    }
}

void Sprite::render(SDL_Renderer* renderer) const {
    if (!texture || !renderer) return;
    SDL_RenderCopy(renderer, texture.get(), &source_rect, &destination_rect);

    if (show_debug_box) {
        SDL_Color color = colliding ? SDL_Color{255,0,0,255} : SDL_Color{0,255,0,255};
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(renderer, &destination_rect);
    }
}

void Sprite::set_position(int x, int y) {
    destination_rect.x = x;
    destination_rect.y = y;
}
