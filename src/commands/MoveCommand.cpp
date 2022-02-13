//
// Created by pollini on 02/02/2022.
//

#include "MoveCommand.h"

#include "AttackCommand.h"
#include "CameraSystem.h"
#include "Map.h"
#include "components/Position.h"
#include "components/Tags.h"

void MoveCommand::execute() {
    auto& ecs = Services::Ecs::ref();

    auto& map = ecs.registry.ctx().at<Map>();
    auto& position = ecs.registry.get<Position>(entity_);

    spdlog::info("MoveCommand: hero ({},{}), dx={}, dy={}, walkable? {}", position.col, position.row, dx, dy,
                 map.isWalkable(position.col + dx, position.row + dy));

    if (map.isWalkable(position.col + dx,
                       position.row + dy)) {  // se la cella di arrivo é camminabile

        auto monstersView = ecs.registry.view<Position, MonsterTag>();

        for (auto monster : monstersView) {
            auto& monsterPosition = ecs.registry.get<Position>(monster);
            if (monsterPosition.col == position.col + dx && monsterPosition.row == position.row + dy) {
                spdlog::debug("MoveCommand: monster ({},{}) in the way", monsterPosition.col, monsterPosition.row);

                //                Commands.Post(new AttackCommand(entity, monster));
                auto& commands = ecs.registry.ctx().at<CommandQueue>();
                commands.push(std::make_shared<AttackCommand>(entity_, monster));
                return;
            }
        }

        position.col += dx;
        position.row += dy;

        // genera evento
        ecs.registry.ctx().at<EventStore>().store(new TestEvent("hero moved"));
        CameraSystem::updateCamera(position.col, position.row);
        CameraSystem::updateViewport();

        auto item = map.getItemAt(position.col, position.row);  // prendi l'oggetto
        // nella cella di arrivo
        if (item != entt::null) {
            const auto named = ecs.registry.get<Named>(item);
            auto name = named.name;
            fmt::print("MoveCommand: found item {}\n", name);
            ecs.registry.ctx().at<EventStore>().store(new ItemFoundEvent(item));
            auto& inventory = ecs.registry.get<Inventory>(entity_);
            inventory.pickUp(item);

            map.removeItemAt(position.col, position.row, item);
        }
    }
}
