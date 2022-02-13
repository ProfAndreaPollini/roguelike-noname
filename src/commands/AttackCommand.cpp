//
// Created by pollini on 13/02/2022.
//

#include "AttackCommand.h"

#include "AttackEvent.h"
#include "EventStore.h"
#include "Services.h"

AttackCommand::AttackCommand(entt::entity attacker, entt::entity target) : attacker(attacker), target(target) {
    auto& ecs = Services::Ecs::ref();
    auto hero = ecs.registry.view<HeroTag>().front();
    isHeroAttack = hero == attacker;
}

void AttackCommand::execute() {
    spdlog::info("AttackCommand::execute()");
    spdlog::info("attacker: {}", static_cast<int>(attacker));
    spdlog::info("target: {}", static_cast<int>(target));
    auto& ecs = Services::Ecs::ref();
    ecs.registry.ctx().at<EventStore>().store(new AttackEvent(attacker, target));
}
