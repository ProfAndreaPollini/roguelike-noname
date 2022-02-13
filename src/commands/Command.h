//
// Created by pollini on 11/01/2022.
//

#ifndef RL_DA_ZERO_COMMAND_H
#define RL_DA_ZERO_COMMAND_H

#include "entt/entity/entity.hpp"

class Command {
   public:
    virtual ~Command() {}
    //    virtual void execute(Entity* entity, Map& map) = 0;
    virtual void execute() = 0;
};

#endif  // RL_DA_ZERO_COMMAND_H
