//
// Created by pollini on 06/02/2022.
//

#include "EntitySpawner.h"

#include "Entity.h"
#include "components/Inventory.h"
#include "components/Position.h"
#include "components/Tags.h"
#include "entt/entt.hpp"

void MonsterSpawner::spawn() {
    auto& ecs = Services::Ecs::ref();
    auto& map = ecs.registry.ctx().at<Map>();
    std::vector<int> roomsBFS = map.roomConnectionsBFS();
    auto view = ecs.registry.view<Position, CellTag>();
    std::set<MapPosition, std::less<MapPosition>> cells;

    for (int i = 0; i < roomsBFS.size(); i++) {
        cells.clear();
        auto room = map.getRoom(roomsBFS[i]);
        for (const entt::entity& cellEntity : room->cells()) {
            const auto [position, cellTag] = view.get<Position, CellTag>(cellEntity);
            auto isWalkable = Cell::isWalkable(cellTag.type);
            if (isWalkable) {
                cells.insert(position);
            }
        }
        spdlog::info("Room {} has {} walkable cells", static_cast<int>(room->id()), cells.size());
        if (i > 1) {
            auto maxMonsters = Rng::getInstance().getRandomInt(5, 10);
            for (int j = 0; j < maxMonsters; j++) {
                if (Rng::getInstance().getRandomInt(0, 100) < 50) {
                    auto spawnPos = *select_random(cells, Rng::getInstance().getRandomInt(0, cells.size() - 1));
                    auto monster = createMonster(spawnPos.row, spawnPos.col);
                    //                    //                    room->addMonster(MonsterType::kGoblin);
                }
            }
        }
    }
}
void ItemSpawner::spawn() {
    // get ecs
    auto& ecs = Services::Ecs::ref();
    auto& map = ecs.registry.ctx().at<Map>();

    // get room connections
    std::vector<int> roomsBFS = map.roomConnectionsBFS();  // TODO: use BFS
    for (int i = 1; i < roomsBFS.size(); i++) {
        auto room = map.getRoom(roomsBFS[i]);              // get room
        const auto& cells = room->getWalkablePositions();  // get walkable cells

        for (int i = 0; i < 5; i++) {  // try to generate items
            if (Rng::getInstance().getRandomInt(0, 100) < 50) {
                const auto& randomCell = *select_random(cells, Rng::getInstance().getRandomInt(0, cells.size() - 1));
                const auto e = room->get(randomCell.col, randomCell.row);
                auto& inventory = ecs.registry.get<Inventory>(e);

                inventory.pickUp(SwordItem::createSword());
            }
        }
    }
}
void DoorAndKeysSpawner::spawn() {
    std::set<entt::entity> createdDoors;
    // get ecs
    auto& ecs = Services::Ecs::ref();
    auto& map = ecs.registry.ctx().at<Map>();
    std::vector<int> roomsBFS = map.roomConnectionsBFS();
    auto doors = map.doors();
    if (doors.size() == 0) {
        return;
    } else if (doors.size() > 4) {
        doors.erase(doors.begin(), select_at(doors, 2));
    }
    for (auto door : doors) {
        if (Rng::getInstance().getRandomInt(0, 100) < 50) {
            auto& ecs = Services::Ecs::ref();
            auto position = ecs.registry.get<Position>(door);
            ecs.registry.remove<CellTag>(door);
            auto& doorTag = ecs.registry.emplace<DoorTag>(door);
            doorTag.glyph = "|";
            doorTag.isOpen = true;
            createdDoors.insert(door);
            //            const auto& room = map.queryRoom(position.col, position.row);

            //            auto key = createKey(position.row, position.col);
        }
    }
    map.setDoors(createdDoors);
}
DoorAndKeysSpawner::DoorAndKeysSpawner(int maxDoors) : maxDoors(maxDoors) {}
