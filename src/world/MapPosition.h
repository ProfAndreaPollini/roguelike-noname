//
// Created by pollini on 26/01/2022.
//

#ifndef RL_DA_ZERO_SRC_WORLD_MAPELEMENT_CPP_MAPPOSITION_H
#define RL_DA_ZERO_SRC_WORLD_MAPELEMENT_CPP_MAPPOSITION_H

struct MapPosition {
    int row{0};
    int col{0};

    MapPosition(int row, int col) : row(row), col(col) {}
    MapPosition() = default;

    bool operator==(const MapPosition& other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const MapPosition& other) const {
        return !(*this == other);
    }

    MapPosition operator+(const MapPosition& other) const {
        return {row + other.row, col + other.col};
    }

    MapPosition operator-(const MapPosition& other) const {
        return {row - other.row, col - other.col};
    }

    MapPosition operator+(int other) const {
        return {row + other, col + other};
    }

    MapPosition operator-(int other) const {
        return {row - other, col - other};
    }

    MapPosition operator*(int other) const {
        return {row * other, col * other};
    }

    MapPosition operator+=(const MapPosition& other) {
        row += other.row;
        col += other.col;
        return *this;
    }

    MapPosition operator-=(const MapPosition& other) {
        row -= other.row;
        col -= other.col;
        return *this;
    }

    // ruota a dx di PI/2
    void rotateRight() {
        int temp = row;
        row = col;
        col = -temp;
    }

    // ruota a dx di howmany PI/2
    void rotateRight(int howMany) {
        for (int i = 0; i < howMany; i++) {
            rotateRight();
        }
    }
} __attribute__((aligned(8)));

#include <functional>
template <>
struct std::hash<MapPosition> {
    std::size_t operator()(MapPosition const& pos) const noexcept {
        std::size_t h1 = std::hash<int>{}(pos.row);
        std::size_t h2 = std::hash<int>{}(pos.col);
        return h1 ^ (h2 << 1);  // or use boost::hash_combine
    }
};

#include <algorithm>
#include <iterator>
#include <random>
#include <vector>

#include "fmt/core.h"
#endif  // RL_DA_ZERO_SRC_WORLD_MAPELEMENT_CPP_MAPPOSITION_H
