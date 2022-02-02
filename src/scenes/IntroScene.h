//
// Created by pollini on 28/01/2022.
//

#ifndef RL_DA_ZERO_SRC_SCENES_INTROSCENE_H
#define RL_DA_ZERO_SRC_SCENES_INTROSCENE_H

#include "Renderer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "extras/raygui.h"
#include "raylib-cpp.hpp"

class IntroScene : public Scene {
   public:
    IntroScene() = default;

    //    ~IntroScene() override = default;

    void update() override {}

    void render() override {
        Renderer::getInstance().prepare();
        Renderer::getInstance().drawText("IntroScene", {10, 10},
                                         {255, 0, 0, 255});
        if (GuiButton((Rectangle){25, 255, 125, 30}, "Start Game"))
            startGame_ = true;
        Renderer::getInstance().draw();
    }
    void handleInput() override;
    //    void onLoad() override
    //    void onUnload() override;
   private:
    bool startGame_ = false;
};

#endif  // RL_DA_ZERO_SRC_SCENES_INTROSCENE_H
