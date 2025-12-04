#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "input.hpp"
#include "scene.hpp"

class SceneManager {
public:
    // get scene ready - not active yet
    template <typename T, typename... Args>
    void add_scene(const std::string& name, Args&&... args) {
        // forward ensures forwarding arguments preserves their init meaning
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

    // access curretn scene
    Scene* get_current_scene() {
        return current_scene;
    }

    const std::string get_current_name() const { return current_scene_name; }

    // forward calls to active scene
    void update(float delta_time, const Input_State& input) {
        if (current_scene) {
            current_scene->update(delta_time, input);
        }
    }

    // render scene
    void render(SDL_Renderer* renderer) {
        if (current_scene) {
            current_scene->render(renderer);
        }
    }

    bool has_scene(const std::string& name) const {
        return scenes.find(name) != scenes.end();
    }

private:
    // list of scenes
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    // pointer to current scene
    Scene* current_scene = nullptr;
    // name of curr scene
    std::string current_scene_name;
};
