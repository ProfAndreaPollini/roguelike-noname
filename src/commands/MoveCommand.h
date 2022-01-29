

#pragma once

#include "Command.h"
#include "Entity.h"

class MoveCommand : public Command {
   public:
    MoveCommand(int dx, int dy) : dx(dx), dy(dy) {}

    virtual ~MoveCommand() = default;

    virtual void execute(Entity* entity, Map& map) override {
//        fmt::print("MoveCommand: hero ({},{}), dx={}, dy={}, walkable? {}\n",entity.x(),entity.y(), dx, dy,map.isWalkable(
//                                                                          entity.x() + dx,
//                                                                          entity.y() + dy));
        if (map.isWalkable(
                entity->x() + dx,
                entity->y() + dy)) {  // se la cella di arrivo é camminabile
            entity->move(dx, dy);
            auto item = map.getItemAt(entity->x(), entity->y()); // prendi l'oggetto nella cella di arrivo
            if (item != nullptr) {
                fmt::print("MoveCommand: found item {}\n", item->name());
                entity->pickUp(item);
               map.removeItemAt(entity->x(), entity->y());
            }
        }
    }

   private:
    int dx;
    int dy;
};