//
// Created by pollini on 09/02/2022.
//

#include "Map.h"
#include "MapRendererSystem.h"
#include "Services.h"

void MapRendererSystem::render(entt::entity heroRoom) {
    const auto& map = Services::Ecs::ref().registry.ctx().at<const Map>();
    const auto& rooms = map.roomGraph();
    const auto& neighbours = rooms.getNeighborsId(heroRoom);
    for (const auto& room : rooms.elements()) {
        Renderer::getInstance().drawRoom(room, heroRoom, neighbours, *viewport_);
    }
}
void MapRendererSystem::updateCamera(Viewport* viewport) { viewport_ = viewport; }
