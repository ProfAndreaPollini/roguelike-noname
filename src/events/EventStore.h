//
// Created by pollini on 29/01/2022.
//

#ifndef RL_DA_ZERO_SRC_EVENTS_EVENTSTORE_H
#define RL_DA_ZERO_SRC_EVENTS_EVENTSTORE_H

#include <memory>
#include <vector>

#include "Event.h"
#include "util.h"

class EventStore {
   public:
    static EventStore& getInstance() {
        static EventStore instance;
        return instance;
    }

    virtual ~EventStore() = default;

    void store(Event* event) {
        events_.emplace_back(event);
        if (events_.size() > 15) {
            events_.erase(events_.begin());
        }
    }

    //    void store(const std::vector<Event>& events){events_.;}
    const std::vector<Rc<Event>>& events() const { return events_; };

   private:
    EventStore() = default;
    EventStore(const EventStore&) = delete;
    EventStore& operator=(const EventStore&) = delete;
    EventStore(EventStore&&) = delete;

    std::vector<Rc<Event>> events_;
};

#endif  // RL_DA_ZERO_SRC_EVENTS_EVENTSTORE_H
