//
// Created by pollini on 02/02/2022.
//

#include "MoveCommand.h"

#include "CameraSystem.h"
#include "Map.h"

void MoveCommand::execute(entt::entity& entity) {
    auto& ecs = Services::Ecs::ref();

    auto& map = ecs.registry.ctx().at<Map>();
    auto& position = ecs.registry.get<Position>(entity);

    spdlog::debug("MoveCommand: hero ({},{}), dx={}, dy={}, walkable? {}", position.col, position.row, dx, dy,
                  map.isWalkable(position.col + dx, position.row + dy));

    if (map.isWalkable(position.col + dx,
                       position.row + dy)) {  // se la cella di arrivo é camminabile
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
            auto& inventory = ecs.registry.get<Inventory>(entity);
            inventory.pickUp(item);

            map.removeItemAt(position.col, position.row, item);
        }
    }
}
