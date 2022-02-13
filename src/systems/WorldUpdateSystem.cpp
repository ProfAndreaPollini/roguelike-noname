//
// Created by pollini on 07/02/2022.
//

#include "WorldUpdateSystem.h"

#include "Services.h"

WorldUpdateSystem::WorldUpdateSystem() : commandQueue_{Services::Ecs::ref().registry.ctx().at<CommandQueue>()} {}

void WorldUpdateSystem::update() const {
    while (!commandQueue_.isEmpty()) {
        // get queue front command
        auto command = commandQueue_.front();
        commandQueue_.pop();

        command->execute();  // execute it
    }
}
