#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "scene.hpp"
#include "input.hpp"

class SceneManager {
public:
    template <typename T, typename... Args>
    void add_scene(const std::string& name, Args&&... args) {
        scenes[name] = std::make_unique<T>(std::forward<Args>(args)...);
    }

    void remove_scene(const std::string& name) {
        auto scene = scenes.find(name);
        if(scene != scenes.end()) {
            if(current_scene_name == name) {
                current_scene = nullptr;
                current_scene_name.clear();
            }
            scenes.erase(scene);
        }
    }

    bool switch_to_scene(const std::string& name) {
        auto scene = scenes.find(name);
        if (scene == scenes.end()) return false;

        if (current_scene) current_scene->on_exit();
        current_scene = scene->second.get();
        current_scene_name = name;
        if (current_scene) current_scene->on_enter();
        return true;
    }

    Scene* get_current_scene() { return current_scene; }
    const std::string get_current_name() const { return current_scene_name; }

    void update(float delta_time, const Input_State& input) {
        if (current_scene) current_scene->update(delta_time, input);
    }

    void render(SDL_Renderer* renderer) {
        if (current_scene) current_scene->render(renderer);
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    Scene* current_scene = nullptr;
    std::string current_scene_name;
};
