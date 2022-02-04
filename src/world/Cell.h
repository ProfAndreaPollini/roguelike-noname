//
// Created by pollini on 12/01/2022.
//

#ifndef RL_DA_ZERO_CELL_H
#define RL_DA_ZERO_CELL_H

//#include "Renderer.h"

#include "Services.h"
#include "components/Inventory.h"
#include "components/Position.h"
#include "components/Tags.h"
#include "entt/entity/entity.hpp"

// struct CellFeature {};

class Cell {
   public:
    //    Cell() : type(CellType::CELL_EMPTY) {}
    //    Cell(CellType type) : type(type) {}
    //
    //    bool isWalkable() const { return type == CellType::CELL_FLOOR; }
    //
    //    bool operator==(const CellType& other) const { return type == other; }

    static bool isWalkable(CellType type) { return type == CellType::CELL_FLOOR; }

    static entt::entity create(CellType type, int row, int col) {
        auto& ecs = Services::Ecs::ref();
        auto cellEntity = ecs.registry.create();
        auto& cellTag = ecs.registry.emplace<CellTag>(cellEntity, type);
        auto& position = ecs.registry.emplace<Position>(cellEntity);
        position.row = row;
        position.col = col;

        ecs.registry.emplace<Inventory>(cellEntity);
    }

    //    CellType type;
    //    Item* item = nullptr;
};

#endif  // RL_DA_ZERO_CELL_H
