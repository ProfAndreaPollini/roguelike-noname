//
// Created by pollini on 10/01/2022.
//

#ifndef RL_DA_ZERO_ENTITY_H
#define RL_DA_ZERO_ENTITY_H

#include "Services.h"
#include "components/Actions.h"
#include "components/Inventory.h"
#include "components/Position.h"
#include "components/Stats.h"
#include "components/Tags.h"

class Item;

class Entity {
   public:
    Entity(int x, int y) : x_(x), y_(y) {}
    virtual ~Entity() = default;
    int x() const { return x_; }
    int y() const { return y_; }

    void move(int dx, int dy) {
        x_ += dx;
        y_ += dy;
    }

    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }

    void set(int x, int y) {
        x_ = x;
        y_ = y;
    }

    virtual void pickUp(Item* item){};

   private:
    int x_;
    int y_;
};

static entt::entity createMonster(int row, int col) {
    auto& ecs = Services::Ecs::ref();
    auto entity = ecs.registry.create();

    auto& position = ecs.registry.emplace<Position>(entity);
    position.setRow(row);
    position.setCol(col);

    auto& tag = ecs.registry.emplace<MonsterTag>(entity);
    tag.glyph = 'M';
    //    ecs.registry.emplace<Actions>(entity);
    ecs.registry.emplace<Inventory>(entity);

    auto& health = ecs.registry.emplace<Health>(entity);
    health.maxHealth = 100;
    health.currentHealth = 100;

    return entity;
}

#endif  // RL_DA_ZERO_ENTITY_H
