

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
    MoveCommand(entt::entity entity, int dx, int dy) : dx(dx), dy(dy), entity_{entity} {}

    virtual ~MoveCommand() = default;

    void execute() override;

   private:
    int dx;
    int dy;
    entt::entity entity_;
};