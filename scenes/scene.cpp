#include "scene.hpp"
#include "camera.hpp"
#include <algorithm>

void Scene::update(float delta_time, const Input_State& input) {
    for (auto& o : objects) o->update(delta_time);
    collider.update();
}

void Scene::render(SDL_Renderer* renderer, const Camera* cam) {
    for (auto& o : objects) o->render(renderer, cam);
}

void Scene::add_object(const std::shared_ptr<Sprite>& obj) {
    if (!obj) return;
    objects.push_back(obj);
    collider.add_sprite(obj);
}

void Scene::remove_object(Sprite* obj) {
    if (!obj) return;
    collider.remove_sprite(obj);
    objects.erase(std::remove_if(objects.begin(), objects.end(),
        [&](const std::shared_ptr<Sprite>& p){ return p.get() == obj; }), objects.end());
}
