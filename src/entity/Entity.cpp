//
// Created by pollini on 06/02/2022.
//
#include "Entity.h"

#include "Services.h"
#include "components/Actions.h"
#include "components/Inventory.h"
#include "components/Named.h"
#include "components/Position.h"
#include "components/Stats.h"
#include "components/Tags.h"

entt::entity createDoor(const char* glyph, entt::entity key, int row, int col) {
    auto& ecs = Services::Ecs::ref();
    auto entity = ecs.registry.create();

    auto& position = ecs.registry.emplace<Position>(entity);
    position.setRow(row);
    position.setCol(col);

    auto& tag = ecs.registry.emplace<DoorTag>(entity);
    tag.glyph = glyph;
    tag.key = key;

    return entity;
}

entt::entity createKey(const char* glyph, const char* name, int row, int col) {
    auto& ecs = Services::Ecs::ref();
    auto entity = ecs.registry.create();

    auto& position = ecs.registry.emplace<Position>(entity);
    position.setRow(row);
    position.setCol(col);

    auto& named = ecs.registry.emplace<Named>(entity);
    named.name = name;

    auto& tag = ecs.registry.emplace<KeyTag>(entity);
    tag.glyph = glyph;

    return entity;
}
entt::entity createMonster(int row, int col) {
    auto& ecs = Services::Ecs::ref();
    auto entity = ecs.registry.create();

    auto& position = ecs.registry.emplace<Position>(entity);
    position.setRow(row);
    position.setCol(col);

    auto& tag = ecs.registry.emplace<MonsterTag>(entity);
    tag.glyph = "M";
    //    ecs.registry.emplace<Actions>(entity);
    ecs.registry.emplace<Inventory>(entity);

    auto& health = ecs.registry.emplace<Health>(entity);
    health.maxHealth = 100;
    health.currentHealth = 100;

    return entity;
}
