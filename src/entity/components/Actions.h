//
// Created by pollini on 01/02/2022.
//

#ifndef RL_DA_ZERO_SRC_ENTITY_COMPONENTS_ACTIONS_H
#define RL_DA_ZERO_SRC_ENTITY_COMPONENTS_ACTIONS_H

#include <Command.h>

#include <vector>

#include "util.h"

struct Actions {
    std::vector<Rc<Command>> commands;
};

#endif  // RL_DA_ZERO_SRC_ENTITY_COMPONENTS_ACTIONS_H
