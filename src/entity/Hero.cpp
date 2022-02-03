//
// Created by pollini on 10/01/2022.
//

#include "Hero.h"

#include "Services.h"
#include "components/Actions.h"
#include "components/Inventory.h"
#include "components/Position.h"
#include "components/Tags.h"

Hero::Hero() : Entity{15, 10} {}
void Hero::createHero() {
    auto& ecs = Services::Ecs::ref();
    auto entity = ecs.registry.create();

    ecs.registry.emplace<Position>(entity, 15, 10);
    ecs.registry.emplace<HeroTag>(entity);
    ecs.registry.emplace<Actions>(entity);
    ecs.registry.emplace<Inventory>(entity);
}
