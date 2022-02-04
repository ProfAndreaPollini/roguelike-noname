//
// Created by pollini on 30/01/2022.
//

#ifndef RL_DA_ZERO_SRC_LIB_MAPALGORITHMS_H
#define RL_DA_ZERO_SRC_LIB_MAPALGORITHMS_H

#include <set>
#include <unordered_map>
#include <vector>

#include "Graph.h"
#include "components/MapPosition.h"

class MapAlgorithm {
   protected:
    std::vector<MapPosition> positions_;
    LatticeGraph<MapPosition> lattice_;

   public:
    void updateFromMap();
    [[maybe_unused]] void updateFromRoom(int x, int y);
    [[nodiscard]] auto neighbors(MapPosition pos) const
        -> std::vector<MapPosition>;
};

class DijkstraMap : public MapAlgorithm {
   public:
    using Element = std::pair<int, MapPosition>;

    DijkstraMap() = default;

    void build(MapPosition start);

   private:
    std::multiset<Element> values_;
};

class AStar : public MapAlgorithm {
   public:
    AStar() = default;

    [[nodiscard]] auto positions() const { return positions_; }

    void setup(MapPosition start, MapPosition goal) {
        start_ = start;
        goal_ = goal;
        path_.clear();
    }

    void findPath();

    [[nodiscard]] auto getPath() const { return path_; }

   private:
    void reconstructPath(std::unordered_map<MapPosition, MapPosition>& cameFrom,
                         MapPosition current);

    std::vector<MapPosition> path_;
    MapPosition start_;
    MapPosition goal_;
};

#endif  // RL_DA_ZERO_SRC_LIB_MAPALGORITHMS_H
