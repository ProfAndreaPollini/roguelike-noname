//
// Created by pollini on 10/01/2022.
//

#ifndef RL_DA_ZERO_HERO_H
#define RL_DA_ZERO_HERO_H

#include <vector>
#include <memory>

#include "Entity.h"
#include "fmt/core.h"
#include "Item.h"

class Hero : public Entity {
public:


    Hero() : Entity{15,10} {}

    void draw() {
        fmt::print("Hero\n");
    }

    void moveLeft() {
        fmt::print("Hero move left\n");
        move(-14, 0);
    }

    void moveRight() {
        fmt::print("Hero move right\n");
        move(14, 0);
    }

    void moveUp() {
        fmt::print("Hero move up\n");
        move(0, -14);
    }

    void moveDown() {
        fmt::print("Hero move down\n");
        move(0, 14);
    }

     void pickUp(Item* item) override  {
        fmt::print("Hero pick up item\n");
        inventoryItems.emplace_back(item);
    }

    std::vector<Item*> getInventory() {
        return inventoryItems;
    }

   private:
    std::vector<Item*> inventoryItems;
};


#endif //RL_DA_ZERO_HERO_H
