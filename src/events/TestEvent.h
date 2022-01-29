//
// Created by pollini on 29/01/2022.
//

#ifndef RL_DA_ZERO_SRC_EVENTS_TESTEVENT_H
#define RL_DA_ZERO_SRC_EVENTS_TESTEVENT_H

#include <string>

#include "Event.h"

class TestEvent : public Event {
   public:
    TestEvent(std::string message) : message(message) {}

    std::string str() const override { return message; }

   private:
    std::string message;
};

#endif  // RL_DA_ZERO_SRC_EVENTS_TESTEVENT_H
