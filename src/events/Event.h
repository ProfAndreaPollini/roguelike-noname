//
// Created by pollini on 29/01/2022.
//

#ifndef RL_DA_ZERO_SRC_EVENTS_EVENT_H
#define RL_DA_ZERO_SRC_EVENTS_EVENT_H

#include <string>

class Event {
   public:
    virtual ~Event() = default;

    virtual std::string str() const = 0;
};

#endif  // RL_DA_ZERO_SRC_EVENTS_EVENT_H
