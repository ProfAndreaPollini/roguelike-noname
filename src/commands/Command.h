//
// Created by pollini on 11/01/2022.
//

#ifndef RL_DA_ZERO_COMMAND_H
#define RL_DA_ZERO_COMMAND_H

#include "Entity.h"
#include "Map.h"

class Command {
public:
  virtual ~Command() {}
  virtual void execute(Entity* entity, Map& map) = 0;
};



#endif //RL_DA_ZERO_COMMAND_H
