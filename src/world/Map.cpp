//
// Created by pollini on 12/01/2022.
//

#include "Map.h"

#include "Renderer.h"
#include "Services.h"
#include "components/Tags.h"

auto Map::getRooms() const -> const std::vector<RoomPtr> { return rooms_.elements(); }
void Map::draw(const Map::RoomPtr& heroRoom) const {
    for (const auto& room : rooms_.elements()) {
        Renderer::getInstance().drawRoom(room, heroRoom, rooms_.getNeighbors(heroRoom), 0, 0);
    }
}
auto Map::roomWithConnectionCount() const -> int {
    int count = 0;
    for (const auto& room : rooms_.elements()) {
        if (room->connectorCount() > 0) {
            count++;
        }
    }
    return count;
}
auto Map::roomCount() const -> int { return rooms_.elements().size(); }

auto Map::queryRoom(int x, int y) const -> Map::RoomPtr {
    for (const auto& room : rooms_.elements()) {
        if (room->contains(x, y)) {
            return room;
        }
    }
    return nullptr;
}
auto Map::getRoomWithConnections() -> Map::RoomPtr {
    auto n = roomWithConnectionCount();
    if (n == 0) {
        return nullptr;
    }

    std::vector<RoomPtr> found;
    for (const auto& element : rooms_.elements()) {
        if (element->connectorCount() > 0) {
            found.push_back(element);
        }
    }

    if (found.empty()) {
        return nullptr;
    }

    return found[Rng::getInstance().getRandomInt(0, found.size() - 1)];
}
auto Map::addPrefabTo(int roomIndex, MapPrefab& prefab) -> bool {
    auto room = getRoomWithConnections();
    const auto connectorEntity = room->connector(Rng::getInstance().getRandomInt(0, room->connectorCount() - 1));

    auto& ecs = Services::Ecs::ref();
    auto connectorInfo = ecs.registry.get<ConnectorTag>(connectorEntity);

    while (!isDirectionFacing(connectorInfo.direction, prefab.selectedConnectorDirection())) {
        prefab.rotateRight();
    }

    //    auto selectedConnectorPos = connector.position();
    //    auto selectedConnectorDir = connector.direction();
    switch (connectorInfo.direction) {
        case Direction::NORTH:
            connectorInfo.position.row -= 1;
            break;
        case Direction::EAST:
            connectorInfo.position.col += 1;
            break;
        case Direction::SOUTH:
            connectorInfo.position.row += 1;
            break;
        case Direction::WEST:
            connectorInfo.position.col -= 1;
            break;
    }
    //    switch (selectedConnectorDir) {
    //        case Direction::NORTH:
    //            selectedConnectorPos.row -= 1;
    //            break;
    //        case Direction::EAST:
    //            selectedConnectorPos.col += 1;
    //            break;
    //        case Direction::SOUTH:
    //            selectedConnectorPos.row += 1;
    //            break;
    //        case Direction::WEST:
    //            selectedConnectorPos.col -= 1;
    //            break;
    //    }
    prefab.setTranslation(connectorInfo.position);

    if (overlaps(prefab)) {
        fmt::print("overlaps\n");
        return false;
    }

    room->removeConnector(connectorEntity);
    prefab.removeSelectedConnector();

    auto newRoom = Room::createFromMapElement(prefab);
    newRoom->spawnItems();
    addRoom(newRoom);
    rooms_.addEdge(room, newRoom);

    return true;
}
