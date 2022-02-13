//
// Created by pollini on 07/02/2022.
//

#ifndef RL_DA_ZERO_SRC_SYSTEMS_WORLDUPDATESYSTEM_H
#define RL_DA_ZERO_SRC_SYSTEMS_WORLDUPDATESYSTEM_H

#include "CommandQueue.h"
class WorldUpdateSystem {
   public:
    WorldUpdateSystem();

    void update() const;

   private:
    CommandQueue& commandQueue_;
};

#endif  // RL_DA_ZERO_SRC_SYSTEMS_WORLDUPDATESYSTEM_H
