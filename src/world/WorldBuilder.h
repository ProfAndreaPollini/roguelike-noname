//
// Created by pollini on 19/01/2022.
//

#ifndef RL_DA_ZERO_WORLDBUILDER_H
#define RL_DA_ZERO_WORLDBUILDER_H

#include <vector>

#include "Map.h"
#include "MapElement.h"
#include "MapPrefab.h"

class WorldBuilder {
   public:
    WorldBuilder();

    void setup();

    void build() {
        auto& map = Services::Ecs::ref().registry.ctx().at<Map>();
        map.finalize();
    }

    void addRoom();

    auto startingPoint() const { return startingPos_; }
    auto startingRoom() const { return startingRoom_; }

   private:
    Map::RoomPtr startingRoom_;
    MapPosition startingPos_;
};

#endif  // RL_DA_ZERO_WORLDBUILDER_H
