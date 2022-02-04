//
// Created by pollini on 13/01/2022.
//

#ifndef RL_DA_ZERO_SWORDITEM_H
#define RL_DA_ZERO_SWORDITEM_H

#include "Item.h"
#include "entt/entt.hpp"

class SwordItem : public Item {
    //   public:
    //    SwordItem() : Item("Sword", 100, 10) {}
    //    ~SwordItem() = default;
    //
    //    virtual const char* getDrawInfo() override { return "S"; }

   public:
    static entt::entity createSword();
};

#endif  // RL_DA_ZERO_SWORDITEM_H
