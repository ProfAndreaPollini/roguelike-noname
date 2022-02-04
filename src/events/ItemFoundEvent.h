//
// Created by pollini on 29/01/2022.
//

#ifndef RL_DA_ZERO_SRC_EVENTS_ITEMFOUNDEVENT_H
#define RL_DA_ZERO_SRC_EVENTS_ITEMFOUNDEVENT_H

#include <string>

#include "Event.h"
#include "Services.h"
#include "components/Named.h"
#include "entt/entt.hpp"
#include "fmt/format.h"

class ItemFoundEvent : public Event {
   public:
    ItemFoundEvent(entt::entity item) : item(item) {}

    entt::entity getItem() { return item; }

    std::string str() const override {
        auto& ecs = Services::Ecs::ref();
        const auto name = ecs.registry.get<Named>(item).name;
        std::string s = fmt::format("Hai trovato: {}.", name);

        return s;
    }

   private:
    entt::entity item;
};

#endif  // RL_DA_ZERO_SRC_EVENTS_ITEMFOUNDEVENT_H
