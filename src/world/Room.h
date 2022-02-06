//
// Created by pollini on 21/01/2022.
//

#ifndef RL_DA_ZERO_ROOM_H
#define RL_DA_ZERO_ROOM_H

#include <memory>
#include <set>
#include <vector>

//#include "Cell.h"
#include "MapElement.h"
#include "MapPrefab.h"
//#include "Rng.h"
//#include "SwordItem.h"
#include "entt/entity/entity.hpp"

// struct RoomElement {
//     Cell cell;
//     MapElementCell position;
//
//     MapPosition coords() const { return position.coords; }
// };

// struct RoomConnector {
//     Cell cell;
//     MapElementConnector connector;
// };

using RoomConnector = MapElementConnector;

class Room {
   public:
    using RoomPtr = std::shared_ptr<Room>;
    using RoomElement = entt::entity;
    using RoomConnector = entt::entity;

    Room();
    ~Room() = default;

    [[maybe_unused]] void addConnectedRoom(RoomPtr room) { connectedRooms_.push_back(room); }

    static auto createFromMapElement(MapPrefab& mapElement) -> RoomPtr;

    //    void addConnection(RoomPtr room) { connectedRooms_.push_back(room); }

    [[nodiscard]] auto cells() const -> const std::set<RoomElement>&;

    auto cells() -> std::set<RoomElement>& { return cells_; }

    //    auto connectedRooms() -> std::vector<RoomPtr>& { return
    //    connectedRooms_; }

    void addConnector(RoomConnector connector);

    [[nodiscard]] auto connectors() const -> const std::set<RoomConnector>&;

    auto connectors() -> std::set<RoomConnector>&;

    auto connector(int index) -> RoomConnector;

    [[nodiscard]] auto connector(int index) const -> const RoomConnector&;

    [[nodiscard]] auto connectorCount() const -> int;

    void spawnItems();

    [[nodiscard]] bool overlaps(const Room& other) const;

    void removeElement(const RoomElement& element);

    void removeConnector(const RoomConnector& connector);

    auto isWalkable(int col, int row) -> bool;

    auto getWalkablePositions() const -> std::vector<MapPosition>;

    entt::entity getItemAt(int col, int row);

    void removeItemAt(int col, int row, entt::entity item);

    auto get(int col, int row) -> entt::entity;

    auto contains(int col, int row) -> bool;

   private:
    std::vector<RoomPtr> connectedRooms_;
    std::set<RoomElement> cells_;
    std::set<RoomConnector> connectors_;

    entt::entity entity_;
};

#endif  // RL_DA_ZERO_ROOM_H
