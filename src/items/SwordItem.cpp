//
// Created by pollini on 13/01/2022.
//

#include "SwordItem.h"

#include "Services.h"
#include "components/Tags.h"
#include "components/Named.h"

entt::entity SwordItem::createSword() {
    auto& ecs = Services::Ecs::ref();
    entt::entity sword = ecs.registry.create();

    auto& itemTag = ecs.registry.emplace<ItemTag>(sword);
    itemTag.type = ItemType::SWORD;

    ecs.registry.emplace<Named>(sword, "Sword");
    return sword;
}
