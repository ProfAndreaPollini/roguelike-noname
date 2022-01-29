//
// Created by pollini on 29/01/2022.
//

#ifndef RL_DA_ZERO_SRC_SCENES_INVENTORYSCENE_H
#define RL_DA_ZERO_SRC_SCENES_INVENTORYSCENE_H

#include "Renderer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "raylib-cpp.hpp"

class InventoryScene : public Scene {
   public:
    void handleInput() override {
        if (IsKeyPressed(KEY_ESCAPE)) {
            SceneManager::getInstance().changeScene("PLAY");
        }
    }
    void update() override {}
    void render() override {
        Renderer::getInstance().prepare();
        DrawRectangle(0, 0, 400, 400, {0, 0, 0, 80});
        DrawText("inventario", 10, 100, 20, {255, 255, 255, 255});
        //        Renderer::getInstance().drawText("inventario", 30, 30,
        //                                         {255, 255, 255, 255});
        Renderer::getInstance().draw();
    }
};

#endif  // RL_DA_ZERO_SRC_SCENES_INVENTORYSCENE_H
