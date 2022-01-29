//
// Created by pollini on 12/01/2022.
//

#ifndef RL_DA_ZERO_CELL_H
#define RL_DA_ZERO_CELL_H

#include <sstream>
//#include "Renderer.h"
#include "Item.h"

enum class CellType {
    CELL_EMPTY = 0,
    CELL_WALL = 1,
    CELL_FLOOR = 2,
};

struct CellFeature {

};

class Cell {
public:
    Cell() : type(CellType::CELL_EMPTY) {}
    Cell(CellType type) : type(type) {}

    bool isWalkable() const {
        return type == CellType::CELL_FLOOR;
    }

    bool operator==(const CellType& other) const {
        return type == other;
    }


    CellType type;
    Item* item = nullptr;
};


#endif //RL_DA_ZERO_CELL_H
