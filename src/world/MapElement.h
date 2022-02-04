//
// Created by pollini on 14/01/2022.
//

#ifndef RL_DA_ZERO_MAPELEMENT_H
#define RL_DA_ZERO_MAPELEMENT_H

#include <algorithm>
#include <iterator>
#include <random>
#include <vector>

#include "components/MapPosition.h"
#include "fmt/core.h"

enum class Direction { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };

Direction rotateDirection(Direction dir, int n);
bool isDirectionFacing(Direction dir1, Direction dir2);

using MapCoord = struct MapPosition;

class MapElementConnector {
   public:
    explicit MapElementConnector(MapCoord position, Direction direction) : position_(position), direction_(direction) {}
    explicit MapElementConnector(int row, int col, Direction direction) : position_(), direction_(direction) {
        position_.setRow(row);
        position_.setCol(col);
    }

    [[nodiscard]] auto direction() const -> Direction { return direction_; }
    [[nodiscard]] auto position() const -> MapCoord { return position_; }
    void setPosition(MapCoord position) { position_ = position; }
    void setDirection(Direction direction) { direction_ = direction; }
    void rotateDirectionRight() { direction_ = rotateDirection(direction_, 1); }

    // ruota rispetto a (0,0)
    void rotatePositionRight() { position_.rotateRight(); }

    void operator+=(const MapCoord& other) { position_ += other; }
    void operator-=(const MapCoord& other) { position_ -= other; }

   private:
    MapCoord position_;
    Direction direction_;
} __attribute__((aligned(16)));

struct MapElementCell {
    //    int row;
    //    int col;
    MapCoord coords;
    unsigned int value;

    MapElementCell(int row, int col, unsigned int value) : value(value) {
        coords.setRow(row);
        coords.setCol(col);
    }

    bool operator==(const MapElementCell& other) const { return coords == other.coords && value == other.value; }
};

class BaseMapElement {
   public:
    void addConnector(int row, int col, Direction direction) {
        MapElementConnector cell(row, col, direction);
        connectors_.push_back(cell);
    }

    [[nodiscard]] auto connectors() const -> std::vector<MapElementConnector> { return connectors_; }

    [[nodiscard]] std::vector<MapElementCell> cells() const { return cells_; }

    [[nodiscard]] MapPosition baricenter() const {
        int row = 0;
        int col = 0;
        for (auto cell : cells_) {
            row += cell.coords.row;
            col += cell.coords.col;
        }
        auto pos = MapPosition();
        pos.setRow(row / cells_.size());
        pos.setCol(col / cells_.size());
        return pos;
    }

    void setTranslation(MapPosition translation) { setTranslation(translation.row, translation.col); }

    void setTranslation(int row, int col) {
        //        MapCoord translation_ = {row, col};
        MapCoord translation_ = {};
        translation_.setRow(row);
        translation_.setCol(col);

        const auto connectorCoords = connectors_[pivot_].position();
        for (auto& cell : cells_) {
            cell.coords -= connectorCoords;
            cell.coords += translation_;
        }

        for (auto& connector : connectors_) {
            connector.setPosition(connector.position() - connectorCoords);
            connector.setPosition(connector.position() + translation_);
        }
    }

    void rotateRight() {
        const auto connectorCoords = connectors_[pivot_].position();

        for (auto& cell : cells_) {
            cell.coords -= connectorCoords;
            cell.coords.rotateRight(1);
            cell.coords += connectorCoords;
        }

        for (auto& connector : connectors_) {
            connector -= connectorCoords;
            connector.rotatePositionRight();
            connector += connectorCoords;
            connector.rotateDirectionRight();
        }
    }

    void setLocalOrigin(int index) {
        if (index >= connectors_.size()) {
            throw std::runtime_error("index out of range");
        }
        pivot_ = index;
    }

    [[nodiscard]] bool overlaps(const BaseMapElement& other) const {
        for (const auto& cell : cells()) {
#pragma clang loop unroll_count(8)
            for (const auto& otherCell : other.cells()) {
                if (otherCell.coords.row == cell.coords.row && otherCell.coords.col == cell.coords.col) {
                    fmt::print("overlaps\n");
                    return true;
                }
            }
        }
        return false;
    }

   protected:
    std::vector<MapElementConnector> connectors_;
    std::vector<MapElementCell> cells_;

    //    MapCoord translation_ = {0, 0};
    //    int rotation_ = 0;
    int pivot_ = 0;
};

#endif  // RL_DA_ZERO_MAPELEMENT_H
