//
// Created by pollini on 29/01/2022.
//

#ifndef RL_DA_ZERO_SRC_SCENES_INVENTORYSCENE_H
#define RL_DA_ZERO_SRC_SCENES_INVENTORYSCENE_H

#include "Renderer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Services.h"
#include "components/Inventory.h"
#include "components/Named.h"
#include "components/Tags.h"
#include "raylib-cpp.hpp"

class InventoryScene : public Scene {
   public:
    void handleInput() override;
    void update() override {}
    void render() override {
        auto& ecs = Services::Ecs::ref();

        auto hero = ecs.registry.view<HeroTag>().front();
        const auto& inventory = ecs.registry.get<Inventory>(hero);

        Renderer::getInstance().prepare();
        DrawRectangle(0, 0, 400, 400, {0, 0, 0, 80});
        DrawText("inventario", 10, 100, 20, {255, 255, 255, 255});
        //        Renderer::getInstance().drawText("inventario", 30, 30,
        //                                         {255, 255, 255, 255});
        for (int i = 0; i < inventory.items.size(); i++) {
            auto& item = inventory.items[i];
            const auto name = ecs.registry.get<Named>(item).name;
            fmt::print("item: {}\n", name);
            //            DrawText("inventario", 10, 100, 20, {255, 255, 255,
            //            255});
            Renderer::getInstance().drawText(TextFormat(name), 5, 5 + i * 1,
                                             {255, 255, 255, 255});
        }

        Renderer::getInstance().draw();
    }
};

#endif  // RL_DA_ZERO_SRC_SCENES_INVENTORYSCENE_H
