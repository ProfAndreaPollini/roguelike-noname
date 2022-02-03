

#pragma once

#include "Command.h"
#include "Entity.h"
#include "EventStore.h"
#include "ItemFoundEvent.h"
#include "Services.h"
#include "TestEvent.h"
#include "components/Inventory.h"
#include "components/Position.h"
#include "entt/entity/entity.hpp"

class MoveCommand : public Command {
   public:
    MoveCommand(int dx, int dy) : dx(dx), dy(dy) {}

    virtual ~MoveCommand() = default;

    void execute(entt::entity& entity) override;

   private:
    int dx;
    int dy;
};