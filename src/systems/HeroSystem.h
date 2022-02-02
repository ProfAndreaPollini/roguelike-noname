//
// Created by pollini on 02/02/2022.
//

#ifndef RL_DA_ZERO_SRC_SYSTEMS_HEROSYSTEM_H
#define RL_DA_ZERO_SRC_SYSTEMS_HEROSYSTEM_H

#include "Services.h"
#include "components/Actions.h"
#include "components/Position.h"
#include "components/Tags.h"

class HeroSystem {
    static void updateHero() {
        auto& ecs = Services::Ecs::ref();

        auto view = ecs.registry.view<HeroTag>();
        for (auto entity : view) {
            auto& actions = ecs.registry.get<Actions>(entity);
            for (auto& action : actions.commands) {
                action->execute(entity);
            }
        }
    }
};

#endif  // RL_DA_ZERO_SRC_SYSTEMS_HEROSYSTEM_H
