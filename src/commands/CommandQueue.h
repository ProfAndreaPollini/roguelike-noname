//
// Created by pollini on 07/02/2022.
//

#ifndef RL_DA_ZERO_SRC_COMMANDS_COMMANDQUEUE_H
#define RL_DA_ZERO_SRC_COMMANDS_COMMANDQUEUE_H

#include <queue>

#include "Command.h"
#include "util.h"

class CommandQueue {
   public:
    void push(const Rc<Command>& command) { commands_.push(command); }
    Rc<Command>& front() { return commands_.front(); }
    void pop() { commands_.pop(); }
    bool isEmpty() const { return commands_.empty(); }

   private:
    std::queue<std::shared_ptr<Command>> commands_;
};

#endif  // RL_DA_ZERO_SRC_COMMANDS_COMMANDQUEUE_H
