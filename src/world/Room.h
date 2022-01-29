//
// Created by pollini on 21/01/2022.
//

#ifndef RL_DA_ZERO_ROOM_H
#define RL_DA_ZERO_ROOM_H

#include <memory>
#include <vector>

#include "Cell.h"
#include "MapElement.h"
#include "MapPosition.h"
#include "MapPrefab.h"
#include "Rng.h"
#include "SwordItem.h"

struct RoomElement {
    Cell cell;
    MapElementCell position;

    MapPosition coords() const { return position.coords; }
};

// struct RoomConnector {
//     Cell cell;
//     MapElementConnector connector;
// };

using RoomConnector = MapElementConnector;

class Room {
   public:
    using RoomPtr = std::shared_ptr<Room>;

    Room() = default;
    ~Room() = default;

    void addConnectedRoom(RoomPtr room) { connectedRooms_.push_back(room); }

    static RoomPtr createFromMapElement(MapPrefab& mapElement);

    void addConnection(RoomPtr room) { connectedRooms_.push_back(room); }

    const std::vector<RoomElement>& cells() const { return cells_; }

    std::vector<RoomElement>& cells() { return cells_; }

    std::vector<RoomPtr>& connectedRooms() { return connectedRooms_; }

    void addConnector(RoomConnector connector) {
        connectors_.push_back(connector);
    }

    [[nodiscard]] const std::vector<RoomConnector>& connectors() const {
        return connectors_;
    }

    std::vector<RoomConnector>& connectors() { return connectors_; }

    RoomConnector& connector(int index) { return connectors_[index]; }

    [[nodiscard]] const RoomConnector& connector(int index) const {
        return connectors_[index];
    }

    [[nodiscard]] int connectorCount() const { return connectors_.size(); }

    void spawnItems() {
        for (int i = 0; i < 5; i++) {
            if (Rng::getInstance().getRandomInt(0, 100) < 50) {
                cells_[Rng::getInstance().getRandomInt(0, cells_.size() - 1)]
                    .cell.item = new SwordItem();
            }
        }
    }

    [[nodiscard]] bool overlaps(const Room& other) const {  // TODO: implement
        for (const auto& cell : cells_) {
            for (const auto& otherCell : other.cells_) {
                if (cell.position.coords == otherCell.position.coords) {
                    return true;
                }
            }
        }
        return false;
    }

    void remove(const RoomElement& element) {
        cells_.erase(std::remove_if(cells_.begin(), cells_.end(),
                                    [&element](const RoomElement& cell) {
                                        return cell.position.coords ==
                                               element.position.coords;
                                    }),
                     cells_.end());
    }

    void remove(const RoomConnector& connector) {
        connectors_.erase(std::remove_if(connectors_.begin(), connectors_.end(),
                                         [&connector](const RoomConnector& c) {
                                             return c.position() ==
                                                    connector.position();
                                         }),
                          connectors_.end());
        RoomElement element = {
            CellType::CELL_FLOOR,
            {connector.position().row, connector.position().col,
             static_cast<unsigned int>(0xffffffff)}};
        cells_.push_back(element);
    }

    auto isWalkable(int col, int row) const -> bool {
        for (const auto& cell : cells_) {
            if (cell.coords().col == col && cell.coords().row == row) {
                return cell.cell.isWalkable();
            }
        }
        return false;
    }

    Item* getItemAt(int col, int row) {
        for (auto& cell : cells_) {
            if (cell.coords().col == col && cell.coords().row == row) {
                if (cell.cell.item) {
                    fmt::print("item = {}\n", cell.cell.item->name());
                    return cell.cell.item;
                    cell.cell.item = nullptr;
                }
            }
        }
        return nullptr;
    }

    void removeItemAt(int col, int row) {
        for (auto& cell : cells_) {
            if (cell.coords().col == col && cell.coords().row == row) {
                cell.cell.item = nullptr;
                return;
            }
        }
    }

    Cell& get(int col, int row) {
        for (auto& cell : cells_) {
            if (cell.coords().col == col && cell.coords().row == row) {
                return cell.cell;
            }
        }
    }

    bool contains(int col, int row) {
        for (const auto& cell : cells_) {
            if (cell.coords().col == col && cell.coords().row == row) {
                return true;
            }
        }
        return false;
    }

   private:
    std::vector<RoomPtr> connectedRooms_;
    std::vector<RoomElement> cells_;
    std::vector<RoomConnector> connectors_;
};

#endif  // RL_DA_ZERO_ROOM_H
