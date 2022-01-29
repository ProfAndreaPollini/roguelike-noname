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

    void addScene(const std::string& name, Rc<Scene> scene) {
        scenes_[name] = scene;
    }

    void removeScene(const std::string& name) {
        scenes_.erase(name);
    }

    void changeScene(const std::string& name) {
        if (currentScene_) {
            currentScene_->onUnload();
        }

        currentScene_ = scenes_[name].get();
        currentScene_->onLoad();
    }

    Scene* getCurrentScene() {
        return currentScene_;
    }

    private:
    SceneManager() {

    }
     SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    Scene* currentScene_;
    std::unordered_map<std::string, Rc<Scene>> scenes_;
};

#endif  // RL_DA_ZERO_SRC_SCENES_SCENEMANAGER_H
