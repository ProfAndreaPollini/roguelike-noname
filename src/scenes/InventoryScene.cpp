//
// Created by pollini on 29/01/2022.
//

#include "InventoryScene.h"

#include "Services.h"

void InventoryScene::handleInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        auto& sceneManager = Services::SceneManager::ref();
        sceneManager.changeScene("PLAY");
    }
}
