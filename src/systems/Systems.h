//
// Created by pollini on 06/02/2022.
//

#ifndef RL_DA_ZERO_SRC_SYSTEMS_SYSTEMS_H
#define RL_DA_ZERO_SRC_SYSTEMS_SYSTEMS_H

#include "Room.h"

class Systems {};

class Map;

void renderMonsterSystem(Room::RoomPtr room);
void renderDoorsSystem(Room::RoomPtr room);
void renderMapSystem(Map* map, Room::RoomPtr room);

#endif  // RL_DA_ZERO_SRC_SYSTEMS_SYSTEMS_H
