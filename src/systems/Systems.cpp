//
// Created by pollini on 06/02/2022.
//

#include "Systems.h"

#include "Map.h"
#include "Services.h"
#include "components/Inventory.h"
#include "components/Position.h"
#include "components/Tags.h"

void renderMapSystem(Map* map, Room::RoomPtr room) {}

void renderMonsterSystem(Room::RoomPtr room) {
    auto& ecs = Services::Ecs::ref();
    auto monstersView = ecs.registry.view<Position, MonsterTag, Inventory>();

    for (auto entity : monstersView) {
        auto& position = monstersView.get<Position>(entity);
        auto& inventory = monstersView.get<Inventory>(entity);
        auto& tags = monstersView.get<MonsterTag>(entity);

        //        if (room->contains(position.col, position.row)) {
        Renderer::getInstance().drawEntity({position.col, position.row, tags.glyph});
        //        }
    }
}
void renderDoorsSystem(Room::RoomPtr room) {
    auto& ecs = Services::Ecs::ref();
    auto doorsView = ecs.registry.view<Position, DoorTag>();
    for (auto entity : doorsView) {
        auto& position = doorsView.get<Position>(entity);
        auto& tags = doorsView.get<DoorTag>(entity);
        Renderer::getInstance().drawEntity({position.col, position.row, tags.glyph});
    }
}
