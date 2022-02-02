//
// Created by pollini on 30/01/2022.
//

#include "MapAlgorithms.h"

#include <algorithm>
#include <queue>
#include <set>
#include <unordered_map>

#include "GameCtx.h"
#include "spdlog/stopwatch.h"
void AStar::findPath() {
    //    std::vector<MapPosition> openSet;

    std::unordered_map<MapPosition, MapPosition> cameFrom;
    std::unordered_map<MapPosition, float> gScore;
    std::unordered_map<MapPosition, float> fScore;

    auto cmp = [&fScore](MapPosition left, MapPosition right) {
        return fScore[left] < fScore[right];
    };
    std::multiset<MapPosition, decltype(cmp)> openSet_multiset(cmp);

    auto heuristic = [](const MapPosition& g, const MapPosition& pos) {
        return (float)(std::fabs(pos.col - g.col) + std::fabs(pos.row - g.row));
    };

    gScore[start_] = 0;
    fScore[start_] = heuristic(goal_, start_);

    //    openSet.push_back(start_);
    openSet_multiset.insert(start_);
    spdlog::stopwatch sw;
    int nloops = 0;
    // auto t = sw.elapsed();
    while (!openSet_multiset.empty()) {
        nloops++;
        // t += sw.elapsed();
        //         std::priority_queue<MapPosition, std::vector<MapPosition>,
        //                             decltype(cmp)>
        //             openSetPQ(openSet.begin(), openSet.end(), cmp);
        //         spdlog::info("openSet size: {}", openSet.size());
        //        auto current = *std::min_element(openSet.begin(),
        //        openSet.end(),
        //                                         cmp);  // openSetPQ.top();

        auto current = *openSet_multiset.begin();
        openSet_multiset.erase(openSet_multiset.begin());
        //        openSet.erase(current);  // erase(openSet.begin());

        //        openSet.erase(std::remove(openSet.begin(), openSet.end(),
        //        current),
        //                      openSet.end());
        if (!gScore.contains(current)) {
            gScore[current] = std::numeric_limits<float>::max();
        }

        if (!fScore.contains(current)) {
            fScore[current] = std::numeric_limits<float>::max();
        }

        if (current == goal_) {
            reconstructPath(cameFrom, current);
            spdlog::info("nloops: {}", nloops);
            spdlog::info("t: {}", sw);
            return;
        }
        for (const auto& neighbor : neighbors(current)) {
            //            if (std::find(openSet_multiset.begin(),
            //            openSet_multiset.end(), neighbor) ==
            //                openSet_multiset.end()) {
            //                openSet_multiset.insert(neighbor);

            //            if (!gScore.contains(neighbor)) {
            //                gScore[neighbor] =
            //                std::numeric_limits<float>::max();
            //                openSet_multiset.insert(neighbor);
            //            } else {
            auto tentativeGScore = gScore[current] + 1;
            if (!gScore.contains(neighbor)) {  //||
                // tentativeGScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentativeGScore;
                fScore[neighbor] = tentativeGScore + heuristic(goal_, neighbor);
                openSet_multiset.insert(neighbor);
            } else {
                if (tentativeGScore < gScore[neighbor]) {
                    cameFrom[neighbor] = current;
                    gScore[neighbor] = tentativeGScore;
                    fScore[neighbor] =
                        tentativeGScore + heuristic(goal_, neighbor);
                    if (!openSet_multiset.contains(neighbor)) {
                        openSet_multiset.insert(neighbor);
                    }
                }
            }
            //            }
        }
        //        spdlog::info("openSet: {}", openSet.size());
        //        reconstructPath(cameFrom, current);
        //        spdlog::info("path: {}", path_.size());
        //        for (const auto& pos : path_) {
        //            spdlog::info("{} {}", pos.row, pos.col);
        //        }
    }
}

void AStar::reconstructPath(
    std::unordered_map<MapPosition, MapPosition>& cameFrom,
    MapPosition current) {
    path_.clear();
    while (current != start_) {
        path_.push_back(current);
        current = cameFrom[current];
    }
}

void MapAlgorithm::updateFromMap() {
    if (positions_.size() > 0) return;
    for (const auto& room : GameCtx::getInstance().map()->getRooms()) {
        for (const auto& walkablePosition : room->getWalkablePositions()) {
            positions_.push_back(walkablePosition);
            //            lattice_.addElement(
            //                std::make_shared<MapPosition>(walkablePosition));
        }
    }
    for (const auto& pos : positions_) {
        auto tentative = {MapPosition{pos.row - 1, pos.col},
                          MapPosition{pos.row + 1, pos.col},
                          MapPosition{pos.row, pos.col - 1},
                          MapPosition{pos.row, pos.col + 1}};
        for (const auto neighbor : tentative) {
            if (std::find(positions_.begin(), positions_.end(), neighbor) !=
                positions_.end()) {
                //                lattice_.addElement(std::make_shared<MapPosition>(neighbor));
                lattice_.addEdge(pos, neighbor);
            }
        }
    }
}
[[maybe_unused]] void MapAlgorithm::updateFromRoom(int x, int y) {
    positions_.clear();
    for (const auto& walkablePosition : GameCtx::getInstance()
                                            .map()
                                            ->queryRoom(x, y)
                                            ->getWalkablePositions()) {
        positions_.push_back(walkablePosition);
    }
}
std::vector<MapPosition> MapAlgorithm::neighbors(MapPosition pos) const {
    //    auto tentative = {
    //        MapPosition{pos.row - 1, pos.col}, MapPosition{pos.row + 1,
    //        pos.col}, MapPosition{pos.row, pos.col - 1}, MapPosition{pos.row,
    //        pos.col + 1}};
    //
    //    std::vector<MapPosition> neighbors;
    //    for (const auto& neighbor : tentative) {
    //        if (std::find(positions_.begin(), positions_.end(), neighbor) !=
    //            positions_.end()) {
    //            neighbors.push_back(neighbor);
    //        }
    //    }
    //    return neighbors;
    auto neighbors = lattice_.getNeighbors(pos);

    return neighbors;
}
void DijkstraMap::build(MapPosition start) {
    std::vector<MapPosition> visited;

    updateFromMap();

    auto cmp = [&](MapPosition left, MapPosition right) { return 1 < 2; };
    std::multiset<MapPosition, decltype(cmp)> openSet_multiset(cmp);

    visited.push_back(start);
}
