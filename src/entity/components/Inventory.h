//
// Created by pollini on 01/02/2022.
//

#ifndef RL_DA_ZERO_SRC_ENTITY_COMPONENTS_INVENTORY_H
#define RL_DA_ZERO_SRC_ENTITY_COMPONENTS_INVENTORY_H

#include <vector>

#include "Item.h"
#include "entt/entity/entity.hpp"

struct Inventory {
    std::vector<entt::entity> items;

    bool hasItems() const { return !items.empty(); }

    void pickUp(entt::entity item) {
        fmt::print("Hero pick up item\n");
        items.emplace_back(item);
        fmt::print("Hero has {} items\n", items.size());
    }

    void removeItem(entt::entity item) {
        fmt::print("Remove item\n");
        items.erase(std::remove(items.begin(), items.end(), item), items.end());
        fmt::print("left {} items\n", items.size());
    }
};

#endif  // RL_DA_ZERO_SRC_ENTITY_COMPONENTS_INVENTORY_H
