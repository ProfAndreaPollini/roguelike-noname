//
// Created by pollini on 28/01/2022.
//

#include "SceneManager.h"

#include "spdlog/spdlog.h"

void SceneManager::changeScene(const std::string& name) {
    if (currentScene_ != nullptr) {
        currentScene_->onUnload();
        spdlog::info("changing scene: {}", fmt::ptr(currentScene_));

        nextScene_ = scenes_[name];
        spdlog::info("to scene: {}", fmt::ptr(nextScene_));
    } else {
        spdlog::info("changing scene: {}", fmt::ptr(currentScene_));
        currentScene_ = scenes_[name];
        spdlog::info("to scene: {}", fmt::ptr(currentScene_));
    }
}
