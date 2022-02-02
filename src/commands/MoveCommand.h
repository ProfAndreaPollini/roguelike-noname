

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

    virtual void execute(Entity* entity, Map& map) override {
        //        fmt::print("MoveCommand: hero ({},{}), dx={}, dy={}, walkable?
        //        {}\n",entity.x(),entity.y(), dx, dy,map.isWalkable(
        //                                                                          entity.x() + dx,
        //
        //                                                                          entity.y() + dy));

        if (map.isWalkable(
                entity->x() + dx,
                entity->y() + dy)) {  // se la cella di arrivo é camminabile
            entity->move(dx, dy);

            // genera evento
            EventStore::getInstance().store(new TestEvent("hero moved"));

            auto item = map.getItemAt(
                entity->x(),
                entity->y());  // prendi l'oggetto nella cella di arrivo
            if (item != nullptr) {
                fmt::print("MoveCommand: found item {}\n", item->name());
                EventStore::getInstance().store(new ItemFoundEvent(item));
                entity->pickUp(item);
                map.removeItemAt(entity->x(), entity->y());
            }
        }
    }

    void execute(entt::entity& entity) override {
        auto& ecs = Services::Ecs::ref();

        auto& map = ecs.registry.ctx().at<Map>();
        auto& position = ecs.registry.get<Position>(entity);

        if (map.isWalkable(
                position.x + dx,
                position.y + dy)) {  // se la cella di arrivo é camminabile
            position.x += dx;
            position.y += dy;

            // genera evento
            EventStore::getInstance().store(new TestEvent("hero moved"));

            auto item =
                map.getItemAt(position.x, position.y);  // prendi l'oggetto
                                                        // nella cella di arrivo
            if (item != nullptr) {
                fmt::print("MoveCommand: found item {}\n", item->name());
                EventStore::getInstance().store(new ItemFoundEvent(item));
                auto& inventory = ecs.registry.get<Inventory>(entity);
                inventory.pickUp(item);
                
                map.removeItemAt(position.x, position.y);
            }
        }
    }

   private:
    int dx;
    int dy;
};