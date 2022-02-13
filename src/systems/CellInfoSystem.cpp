//
// Created by pollini on 13/02/2022.
//

#include "CellInfoSystem.h"

#include "Map.h"
#include "Services.h"
#include "raylib.h"

void CellInfoSystem::run(const raylib::Camera2D& camera) const {
    auto mousePosition = GetMousePosition();
    auto mouseWorld = camera.GetScreenToWorld(mousePosition);
    auto cellX = std::floor(mouseWorld.x / Renderer::getInstance().getTileSize().x);
    auto cellY = std::floor(mouseWorld.y / Renderer::getInstance().getTileSize().y);
    auto& ecs = Services::Ecs::ref();
    
    auto monstersView = ecs.registry.view<Position, MonsterTag>();

    for (auto monster : monstersView) {
        auto& monsterPosition = ecs.registry.get<Position>(monster);
        if (monsterPosition.col == cellX && monsterPosition.row == cellY) {
            spdlog::debug("Monster  at ({},{}) ", monsterPosition.col, monsterPosition.row);
            raylib::DrawText(TextFormat("Monster on cell: %f, %f", cellX, cellY), mousePosition.x + 20,
                             mousePosition.y + 50, 20, raylib::WHITE);
        }
    }

    raylib::DrawText(TextFormat("Mouse on cell: %f, %f", cellX, cellY), mousePosition.x + 20, mousePosition.y + 30, 20,
                     LIGHTGRAY);
}
