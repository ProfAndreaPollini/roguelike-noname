//
// Created by pollini on 08/02/2022.
//

#ifndef RL_DA_ZERO_SRC_WORLD_ROOMGRAPH_H
#define RL_DA_ZERO_SRC_WORLD_ROOMGRAPH_H

#include <memory>

#include "Graph.h"
#include "Room.h"
#include "entt/entt.hpp"

class RoomGraph : public Graph<std::shared_ptr<Room>> {
   public:
    std::set<entt::entity> getNeighborsId(ElementPtr element) const {
        std::set<entt::entity> neighbors;
        auto localEdges = edges();
        if (localEdges.contains(element)) {
            for (const auto& edge : localEdges.at(element)) {
                neighbors.insert(edge.to->id());
            }
        }
        return neighbors;
    }
    std::set<entt::entity> getNeighborsId(entt::entity elementId) const {
        std::set<entt::entity> neighbors;
        auto localEdges = edges();
        // create entity edges id set
        std::set<entt::entity> localEdgesIds;
        for (const auto& edge : localEdges) {
            localEdgesIds.insert(edge.first->id());
        }

        //        if (localEdgesIds.contains(elementId)) {
        //            for (const auto& edge : localEdges.at(element)) {
        //                neighbors.insert(edge.to->id());
        //            }
        //        }
        return neighbors;
    }

   private:
    std::set<entt::entity> localEdgesIds;
};

#endif  // RL_DA_ZERO_SRC_WORLD_ROOMGRAPH_H
