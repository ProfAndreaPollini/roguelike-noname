//
// Created by pollini on 09/02/2022.
//

#ifndef RL_DA_ZERO_SRC_SYSTEMS_MAPRENDERERSYSTEM_H
#define RL_DA_ZERO_SRC_SYSTEMS_MAPRENDERERSYSTEM_H

class Map;
#include "components/Viewport.h"
#include "entt/entt.hpp"

class MapRendererSystem {
   public:
    MapRendererSystem() = default;
    ~MapRendererSystem() = default;

    void updateCamera(Viewport* viewport);

    void render(entt::entity heroRoom);

   private:
    //    const Map& map_;
    Viewport* viewport_;
};

#endif  // RL_DA_ZERO_SRC_SYSTEMS_MAPRENDERERSYSTEM_H
