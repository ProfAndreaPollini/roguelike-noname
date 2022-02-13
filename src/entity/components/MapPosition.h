//
// Created by pollini on 26/01/2022.
//

#ifndef RL_DA_ZERO_SRC_WORLD_MAPELEMENT_CPP_MAPPOSITION_H
#define RL_DA_ZERO_SRC_WORLD_MAPELEMENT_CPP_MAPPOSITION_H

#include "spdlog/spdlog.h"

struct MapPosition {
    int row{0};
    int col{0};

    static MapPosition fromRowCol(int row, int col) {
        MapPosition mp;
        mp.row = row;
        mp.col = col;
        return mp;
    }

    MapPosition() = default;
    MapPosition(int row, int col) : row(row), col(col) {}
    MapPosition& operator=(const MapPosition&) = default;
    MapPosition& operator=(MapPosition&&) = default;
    MapPosition(const MapPosition&) = default;

    void setRow(int row) { this->row = row; }

    void setCol(int col) { this->col = col; }

    bool operator==(const MapPosition& other) const { return row == other.row && col == other.col; }

    bool operator!=(const MapPosition& other) const { return !(row == other.row && col == other.col); }

    MapPosition operator+(const MapPosition& other) const { return {row + other.row, col + other.col}; }

    MapPosition operator-(const MapPosition& other) const { return {row - other.row, col - other.col}; }

    MapPosition operator+(int other) const { return {row + other, col + other}; }

    MapPosition operator-(int other) const { return {row - other, col - other}; }

    MapPosition operator*(int other) const { return {row * other, col * other}; }

    MapPosition operator+=(const MapPosition& other) {
        row += other.row;
        col += other.col;
        return *this;
    }

    int operator<=>(const MapPosition& other) const {
        if (row < other.row) {
            return -1;
        } else if (row > other.row) {
            return 1;
        } else if (col < other.col) {
            return -1;
        } else if (col > other.col) {
            return 1;
        } else {
            return 0;
        }
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

   private:
    //    MapPosition(int row, int col) : row(row), col(col) {}
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

//namespace std {
//template <>
//struct less<MapPosition> {
//    bool operator()(const MapPosition& lhs, const MapPosition& rhs) const {
//        spdlog::info("lhs: {} , rhs: {}", lhs.row * 100000 + lhs.col, rhs.col + rhs.row * 10000);
//        return lhs.row * 100000 + lhs.col < rhs.col + rhs.row * 10000;
//    }
//};
//}  // namespace std
#include <algorithm>
#include <iterator>
#include <random>
#include <vector>

#include "fmt/core.h"
#endif  // RL_DA_ZERO_SRC_WORLD_MAPELEMENT_CPP_MAPPOSITION_H
