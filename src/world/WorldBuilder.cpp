//
// Created by pollini on 19/01/2022.
//

#include "WorldBuilder.h"

#include "MapPrefabs.h"
#include "Services.h"

WorldBuilder::WorldBuilder() {}

void WorldBuilder::addRoom() {
    auto& map = Services::Ecs::ref().registry.ctx().at<Map>();
    int attempts = 0;
    auto otherPrefabIndex = 0;
    MapPrefab otherPrefab;

    std::vector<MapPrefab> mapElements = MapPrefabs::getInstance().getPrefabs();

    while (attempts < 10) {
        if (attempts == 0) {
            otherPrefabIndex = Rng::getInstance().getRandomInt(0, mapElements.size() - 1);

            otherPrefab = mapElements[otherPrefabIndex];
        }
        auto roomIdx = Rng::getInstance().getRandomInt(0, map.roomWithConnectionCount() - 1);
        auto added = map.addPrefabTo(roomIdx, otherPrefab);
        if (added) {
            fmt::print("Added prefab to room {}\n", roomIdx);
            fmt::print("rooms = {}\n", map.roomCount());
            attempts = 0;
            break;
        } else {
            fmt::print(".");
            attempts++;
        }
    }
}

void WorldBuilder::setup() {
    auto& map = Services::Ecs::ref().registry.ctx().at<Map>();
    MapPrefabs::getInstance().LoadConfig("config");

    auto prefab = MapPrefabs::getInstance().getPrefab("prefab3");
    auto prefab2 = MapPrefabs::getInstance().getPrefab("prefab2");
    auto prefab3 = MapPrefabs::getInstance().getPrefab("prefab4");

    std::vector<MapPrefab> mapElements = MapPrefabs::getInstance().getPrefabs();

    prefab.centerToConnectorPosition(0);
    prefab2.centerToConnectorPosition(0);
    prefab3.centerToConnectorPosition(0);

    auto currentPrefabIndex = Rng::getInstance().getRandomInt(0, mapElements.size() - 1);
    auto currentPrefab = mapElements[currentPrefabIndex];
    currentPrefab.setTranslation(200, 200);

    std::shared_ptr<Room> currentRoom = Room::createFromMapElement(currentPrefab);

    startingPos_ = currentPrefab.baricenter();

    startingRoom_ = Room::createFromMapElement(currentPrefab);
    startingRoom_->setVisited(true);
    map.addRoom(startingRoom_);
}
