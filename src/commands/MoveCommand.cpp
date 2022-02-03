//
// Created by pollini on 02/02/2022.
//

#include "MoveCommand.h"

#include "CameraSystem.h"

void MoveCommand::execute(entt::entity& entity) {
    auto& ecs = Services::Ecs::ref();

    auto& map = ecs.registry.ctx().at<Map>();
    auto& position = ecs.registry.get<Position>(entity);

    spdlog::debug("MoveCommand: hero ({},{}), dx={}, dy={}, walkable? {}",
                  position.x, position.y, dx, dy,
                  map.isWalkable(position.x + dx, position.y + dy));

    if (map.isWalkable(
            position.x + dx,
            position.y + dy)) {  // se la cella di arrivo é camminabile
        position.x += dx;
        position.y += dy;

        // genera evento
        ecs.registry.ctx().at<EventStore>().store(new TestEvent("hero moved"));
        CameraSystem::updateCamera(position.x, position.y);
        CameraSystem::updateViewport();

        auto item = map.getItemAt(position.x, position.y);  // prendi l'oggetto
        // nella cella di arrivo
        if (item != nullptr) {
            fmt::print("MoveCommand: found item {}\n", item->name());
            ecs.registry.ctx().at<EventStore>().store(new ItemFoundEvent(item));
            auto& inventory = ecs.registry.get<Inventory>(entity);
            inventory.pickUp(item);

            map.removeItemAt(position.x, position.y);
        }
    }
}
