//
// Created by pollini on 12/01/2022.
//

#ifndef RL_DA_ZERO_MAP_H
#define RL_DA_ZERO_MAP_H

#include <spdlog/spdlog.h>

#include <algorithm>
#include <memory>
#include <set>

#include "Cell.h"
#include "Entity.h"
#include "Room.h"
#include "RoomGraph.h"
#include "SwordItem.h"
#include "util.h"

class Map {
   public:
    using RoomPtr = std::shared_ptr<Room>;

    ~Map() = default;

    Map() = default;
    //    Map(int width, int height) : width_(width), height_(height) {}

    [[nodiscard]] auto overlaps(std::shared_ptr<Room> room) const -> bool {
        auto rooms = rooms_.elements();
        for (const auto& otherRoom : rooms) {
            //            auto *other = otherRoom.get();
            if (room->overlaps(*otherRoom)) {
                return true;
            }
        }
        return false;
    }

    auto overlaps(MapPrefab& prefab) -> bool {
        auto rooms = rooms_.elements();
        for (const auto& room : rooms) {
            for (const auto& cell : prefab.cells()) {
                if (room->contains(cell.coords.col, cell.coords.row)) {
                    return true;
                }
                //                for (const auto& otherCell : room->cells()) {
                //                    if (cell.coords ==
                //                    otherCell.position.coords) {
                //                        return true;
                //                    }
                //                }
            }
        }

        return false;
    }

    void addRoom(const std::shared_ptr<Room>& room) {
        if (!overlaps(room)) {
            rooms_.addElement(room);
        }
    }

    void draw(const RoomPtr& heroRoom) const;

    auto isWalkable(int x, int y) const -> bool {
        const auto room = queryRoom(x, y);
        if (room) {
            return room->isWalkable(x, y);
        }
        //        for (const auto& room : rooms_.elements()) {
        //            if (room->isWalkable(x, y)) {
        //                return true;
        //            }
        //        }
        return false;
    }

    auto addPrefabTo(int roomIndex, MapPrefab& prefab) -> bool;

    auto getItemAt(int col, int row) -> entt::entity {
        const auto room = queryRoom(col, row);
        // for (const auto& room : rooms_.elements()) {
        if (room->contains(col, row)) {
            return room->getItemAt(col, row);
        }
        //}
        return entt::null;
    }

    void removeItemAt(int col, int row, entt::entity item) {
        const auto room = queryRoom(col, row);
        // for (const auto& room : rooms_.elements()) {
        if (room->contains(col, row)) {
            room->removeItemAt(col, row, item);
        }
        //}
    }

    [[maybe_unused]] auto getRoom(int index) const -> const Room& { return *rooms_.elements()[index]; }

    [[maybe_unused]] auto getRoom(int index) -> RoomPtr { return rooms_.elementAt(index); }

    auto getRoomWithConnections() -> RoomPtr;

    auto queryRoom(int x, int y) const -> RoomPtr;

    /// Returns the number of rooms
    [[nodiscard]] auto roomCount() const -> int;

    auto getRooms() const -> const std::vector<RoomPtr>;

    /// Returns the number of rooms with at least one connection
    [[nodiscard]] auto roomWithConnectionCount() const -> int;

    std::vector<int> roomConnectionsBFS() {
        if (roomsBFS_.size() == 0) {
            roomsBFS_ = rooms_.BFS();
        }
        return roomsBFS_;
    }

    //    void generateMonsters() {
    //        std::vector<int> roomsBFS = rooms_.BFS();
    //        for (int i = 0; i < roomsBFS.size(); i++) {
    //            auto room = rooms_.elementAt(roomsBFS[i]);
    //            const auto& cells = room->getWalkablePositions();
    //            if (i > 1) {
    //                auto maxMonsters = Rng::getInstance().getRandomInt(5, 10);
    //                for (int j = 0; j < maxMonsters; j++) {
    //                    if (Rng::getInstance().getRandomInt(0, 100) < 50) {
    //                        auto spawnPos = *select_random(cells, Rng::getInstance().getRandomInt(0, cells.size()));
    //                        auto monster = createMonster(spawnPos.row, spawnPos.col);
    //                        //                    //                    room->addMonster(MonsterType::kGoblin);
    //                    }
    //                }
    //            }
    //        }
    //    }

    void finalize() {
        for (const auto& room : rooms_.elements()) {
            room->finalize();
        }
    }

    auto doors() const -> const std::set<entt::entity> { return doors_; }
    void setDoors(const std::set<entt::entity>& doors) { doors_ = doors; }
    //    void makeDoor(entt::entity cellEntity);

    auto getNeighborsId(RoomPtr room) const { return rooms_.getNeighborsId(room); }

    auto roomGraph() const -> const RoomGraph& { return rooms_; }

   private:
    //    int width_;
    //    int height_;

    RoomGraph rooms_;
    // Graph<std::shared_ptr<Room>> rooms_;
    std::set<entt::entity> doors_;
    std::vector<int> roomsBFS_;
};

#endif  // RL_DA_ZERO_MAP_H
