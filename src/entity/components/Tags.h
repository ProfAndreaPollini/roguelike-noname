//
// Created by pollini on 01/02/2022.
//

#ifndef RL_DA_ZERO_SRC_ENTITY_COMPONENTS_TAGS_H
#define RL_DA_ZERO_SRC_ENTITY_COMPONENTS_TAGS_H

#include <map>

#include "entt/entt.hpp"
#include "raylib-cpp.hpp"

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
struct MonsterTag {
    const char* glyph;
};

struct ItemTag {
    ItemType type;
};
struct RoomTag {};
struct CellTag {
    CellType type;
    entt::entity room;
    std::set<entt::entity> entities;
};
struct ConnectorTag {
    Direction direction;
    MapPosition position;
};

struct KeyTag {
    const char* glyph;
};

struct DoorTag {
    const char* glyph;
    entt::entity key;
    bool isOpen;

    DoorTag() : isOpen(false) {}
};

class RenderInfo {
   public:
    raylib::Color bgColor{0, 0, 0, 0};
    raylib::Color textColor{0, 0, 0, 0};
    char glyph;
};

static std::map<CellType, RenderInfo> RenderSpritesheet = {
    {CellType::CELL_FLOOR, {.bgColor = GREEN, .textColor = {80, 80, 80, 255}, .glyph = '.'}},
    {CellType::CELL_WALL, {.bgColor = BLACK, .textColor = WHITE, .glyph = '#'}},
};

#endif  // RL_DA_ZERO_SRC_ENTITY_COMPONENTS_TAGS_H
