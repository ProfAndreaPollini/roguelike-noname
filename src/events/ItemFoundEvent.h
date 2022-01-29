//
// Created by pollini on 29/01/2022.
//

#ifndef RL_DA_ZERO_SRC_EVENTS_ITEMFOUNDEVENT_H
#define RL_DA_ZERO_SRC_EVENTS_ITEMFOUNDEVENT_H

#include <string>

#include "Event.h"
#include "Item.h"

class ItemFoundEvent : public Event {
   public:
    ItemFoundEvent(Item* item) : item(item) {}

    Item* getItem() { return item; }

    std::string str() const override {
        std::string s = fmt::format("Hai trovato: {}.", item->name());

        return s;
    }

   private:
    Item* item;
};

#endif  // RL_DA_ZERO_SRC_EVENTS_ITEMFOUNDEVENT_H
