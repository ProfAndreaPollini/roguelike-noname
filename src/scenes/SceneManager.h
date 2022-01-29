//
// Created by pollini on 28/01/2022.
//

#ifndef RL_DA_ZERO_SRC_SCENES_SCENEMANAGER_H
#define RL_DA_ZERO_SRC_SCENES_SCENEMANAGER_H

#include <memory>
#include <unordered_map>

#include "Scene.h"
#include "util.h"

class SceneManager {
   public:
    static SceneManager& getInstance() {
        static SceneManager instance;
        return instance;
    }

    void addScene(const std::string& name, Scene* scene) {
        scenes_[name] = scene;
    }

    void removeScene(const std::string& name) { scenes_.erase(name); }

    void changeScene(const std::string& name);

    Scene* updateSceneIfNeeded() {
        if (currentScene_ != nextScene_ and nextScene_ != nullptr) {
            currentScene_ = nextScene_;
            nextScene_ = nullptr;
            currentScene_->onLoad();

        }
            return currentScene_;

    }

    Scene* getCurrentScene() { return currentScene_; }

    ~SceneManager() {
        for (auto& scene : scenes_) {
            delete scene.second;
        }
    }

   private:
    SceneManager() {}
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    Scene* currentScene_;
    Scene* nextScene_;
    std::unordered_map<std::string, Scene*> scenes_;
};

#endif  // RL_DA_ZERO_SRC_SCENES_SCENEMANAGER_H
