//
// Created by pollini on 01/02/2022.
//

#ifndef RL_DA_ZERO_SRC_ENTITY_COMPONENTS_TAGS_H
#define RL_DA_ZERO_SRC_ENTITY_COMPONENTS_TAGS_H

enum class CellType {
    CELL_EMPTY = 0,
    CELL_WALL = 1,
    CELL_FLOOR = 2,
    CELL_DEBUG = 3,
};

enum class ItemType {
    SWORD = 0,
    BOW = 1,
};

struct HeroTag {};
struct ItemTag {
    ItemType type;
};
struct RoomTag {};
struct CellTag {
    CellType type;
};
struct ConnectorTag {
    Direction direction;
    MapPosition position;
};

#endif  // RL_DA_ZERO_SRC_ENTITY_COMPONENTS_TAGS_H
