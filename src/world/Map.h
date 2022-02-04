//
// Created by pollini on 12/01/2022.
//

#ifndef RL_DA_ZERO_MAP_H
#define RL_DA_ZERO_MAP_H

#include <spdlog/spdlog.h>

#include <algorithm>
#include <memory>

#include "Cell.h"
#include "Graph.h"
#include "Room.h"
#include "SwordItem.h"

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
        for (const auto& room : rooms_.elements()) {
            if (room->contains(col, row)) {
                return room->getItemAt(col, row);
            }
        }
        return entt::null;
    }

    void removeItemAt(int col, int row) {
        for (const auto& room : rooms_.elements()) {
            if (room->contains(col, row)) {
                room->removeItemAt(col, row);
            }
        }
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
        std::vector<int> roomsBFS = rooms_.BFS();
        return roomsBFS;
    }

   private:
    //    int width_;
    //    int height_;

    Graph<std::shared_ptr<Room>> rooms_;
};

#endif  // RL_DA_ZERO_MAP_H
