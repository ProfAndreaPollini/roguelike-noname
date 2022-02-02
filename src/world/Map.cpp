//
// Created by pollini on 12/01/2022.
//

#include "Map.h"
#include "Renderer.h"

auto Map::getRooms() const -> const std::vector<RoomPtr> {
    return rooms_.elements();
}
void Map::draw(const Map::RoomPtr& heroRoom) const {
    for (const auto& room : rooms_.elements()) {
        Renderer::getInstance().drawRoom(room, heroRoom, 0, 0);
    }
}
