//
// Created by pollini on 28/01/2022.
//

#include "IntroScene.h"

#include "Services.h"

void IntroScene::handleInput() {
    if (startGame_) {
        auto& sceneManager = Services::SceneManager::ref();
        sceneManager.changeScene("PLAY");
    }
}
