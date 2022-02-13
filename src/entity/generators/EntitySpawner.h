//
// Created by pollini on 06/02/2022.
//

#ifndef RL_DA_ZERO_SRC_ENTITY_GENERATORS_ENTITYSPAWNER_H
#define RL_DA_ZERO_SRC_ENTITY_GENERATORS_ENTITYSPAWNER_H

#include "Map.h"
#include "util.h"

class EntitySpawner {
   public:
    virtual void spawn() = 0;
};

class MonsterSpawner : public EntitySpawner {
   public:
    void spawn() override;
};

class ItemSpawner : public EntitySpawner {
   public:
    void spawn() override;
};

class DoorAndKeysSpawner : public EntitySpawner {
   public:
    void spawn() override;
    int maxDoors;
    DoorAndKeysSpawner(int max_doors);
};

#endif  // RL_DA_ZERO_SRC_ENTITY_GENERATORS_ENTITYSPAWNER_H
