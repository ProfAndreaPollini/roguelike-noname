//
// Created by pollini on 13/02/2022.
//

#ifndef RL_DA_ZERO_SRC_EVENTS_ATTACKEVENT_H
#define RL_DA_ZERO_SRC_EVENTS_ATTACKEVENT_H

#include "Event.h"
#include "entt/fwd.hpp"

class AttackEvent : public Event {
   public:
    AttackEvent(entt::entity attacker, entt::entity target) : attacker(attacker), target(target) {}

    ~AttackEvent() override = default;
    std::string str() const override;

   private:
    entt::entity attacker;
    entt::entity target;
};

#endif  // RL_DA_ZERO_SRC_EVENTS_ATTACKEVENT_H
