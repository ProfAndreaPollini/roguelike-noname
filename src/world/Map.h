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
                for (const auto& otherCell : room->cells()) {
                    if (cell.coords == otherCell.position.coords) {
                        return true;
                    }
                }
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

    [[nodiscard]] auto isWalkable(int x, int y) const -> bool {
        for (const auto& room : rooms_.elements()) {
            if (room->isWalkable(x, y)) {
                return true;
            }
        }
        return false;
    }

    auto addPrefabTo(int roomIndex, MapPrefab& prefab) -> bool {
        auto room = getRoomWithConnections();
        const auto connector = room->connector(
            Rng::getInstance().getRandomInt(0, room->connectorCount() - 1));

        while (!isDirectionFacing(connector.direction(),
                                  prefab.selectedConnectorDirection())) {
            prefab.rotateRight();
        }

        auto selectedConnectorPos = connector.position();
        auto selectedConnectorDir = connector.direction();
        switch (selectedConnectorDir) {
            case Direction::NORTH:
                selectedConnectorPos.row -= 1;
                break;
            case Direction::EAST:
                selectedConnectorPos.col += 1;
                break;
            case Direction::SOUTH:
                selectedConnectorPos.row += 1;
                break;
            case Direction::WEST:
                selectedConnectorPos.col -= 1;
                break;
        }
        prefab.setTranslation(selectedConnectorPos);

        if (overlaps(prefab)) {
            fmt::print("overlaps\n");
            return false;
        }

        room->remove(connector);
        prefab.removeSelectedConnector();

        auto newRoom = Room::createFromMapElement(prefab);
        newRoom->spawnItems();
        addRoom(newRoom);
        rooms_.addEdge(room, newRoom);

        return true;
    }

    auto getItemAt(int col, int row) -> Item* {
        for (const auto& room : rooms_.elements()) {
            if (room->contains(col, row)) {
                return room->getItemAt(col, row);
            }
        }
        return nullptr;
    }

    void removeItemAt(int col, int row) {
        for (const auto& room : rooms_.elements()) {
            if (room->contains(col, row)) {
                room->removeItemAt(col, row);
            }
        }
    }

    [[maybe_unused]] auto getRoom(int index) const -> const Room& {
        return *rooms_.elements()[index];
    }

    [[maybe_unused]] auto getRoom(int index) -> RoomPtr {
        return rooms_.elementAt(index);
    }

    auto getRoomWithConnections() -> RoomPtr {
        auto n = roomWithConnectionCount();
        if (n == 0) {
            return nullptr;
        }
        auto elements = rooms_.elements();
        std::vector<RoomPtr> found;
        for (const auto& element : elements) {
            if (element->connectorCount() > 0) {
                found.push_back(element);
            }
        }

        if (found.empty()) {
            return nullptr;
        }

        return found[Rng::getInstance().getRandomInt(0, found.size() - 1)];
    }

    auto queryRoom(int x, int y) -> RoomPtr {
        for (const auto& room : rooms_.elements()) {
            if (room->contains(x, y)) {
                return room;
            }
        }
        return nullptr;
    }

    /// Returns the number of rooms
    [[nodiscard]] auto roomCount() const -> int {
        return rooms_.elements().size();
    }

    auto getRooms() const -> const std::vector<RoomPtr>;

    /// Returns the number of rooms with at least one connection
    [[nodiscard]] auto roomWithConnectionCount() const -> int {
        int count = 0;
        for (const auto& room : rooms_.elements()) {
            if (room->connectorCount() > 0) {
                count++;
            }
        }
        return count;
    }

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
