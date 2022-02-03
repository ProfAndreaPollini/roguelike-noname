//
// Created by pollini on 01/02/2022.
//

#ifndef RL_DA_ZERO_SRC_ENTITY_COMPONENTS_INVENTORY_H
#define RL_DA_ZERO_SRC_ENTITY_COMPONENTS_INVENTORY_H

#include <vector>

#include "Item.h"

struct Inventory {
    std::vector<Item*> items;

    void pickUp(Item* item) {
        fmt::print("Hero pick up item\n");
        items.emplace_back(item);
        fmt::print("Hero has {} items\n", items.size());
    }
};

#endif  // RL_DA_ZERO_SRC_ENTITY_COMPONENTS_INVENTORY_H
