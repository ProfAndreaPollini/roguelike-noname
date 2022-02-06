//
// Created by pollini on 21/01/2022.
//

#include "Room.h"

#include <spdlog/spdlog.h>

#include "Cell.h"
#include "MapPrefab.h"
#include "Services.h"
#include "SwordItem.h"
#include "components/Inventory.h"
#include "components/Named.h"
#include "components/Position.h"
#include "components/Tags.h"

Room::RoomPtr Room::createFromMapElement(MapPrefab& mapElement) {
    auto room = std::make_shared<Room>();
    auto& ecs = Services::Ecs::ref();

    for (const auto& cell : mapElement.cells()) {
        auto cellEntity = ecs.registry.create();

        auto& cellTag = ecs.registry.emplace<CellTag>(cellEntity, CellType::CELL_WALL);
        if (cell.value == 0xffffffff) {
            cellTag.type = CellType::CELL_FLOOR;
        }

        auto& position = ecs.registry.emplace<Position>(cellEntity);
        position.setRow(cell.coords.row);
        position.setCol(cell.coords.col);

        ecs.registry.emplace<Inventory>(cellEntity);

        room->cells().insert(cellEntity);
    }

    for (auto& connector : mapElement.connectors()) {
        auto connectorEntity = ecs.registry.create();
        auto& connectorInfo = ecs.registry.emplace<ConnectorTag>(connectorEntity);
        connectorInfo.position = connector.position();
        connectorInfo.direction = connector.direction();

        room->addConnector(connectorEntity);
    }

    //        room->mapElement_ = mapElement;
    //    for (auto& cell : mapElement.cells()) {
    //        Cell c{CellType::CELL_WALL};
    //        if (cell.value == 0xffffffff) {
    //            c.type = CellType::CELL_FLOOR;
    //        }
    //        RoomElement roomElement{c, cell};
    //        room->cells().push_back(roomElement);
    //        //.push_back({c,cell.coords});
    //    }
    //
    //    for (auto& connector : mapElement.connectors()) {
    //        room->addConnector(connector);
    //    }

    return room;
}

Room::Room() {
    auto& ecs = Services::Ecs::ref();
    entity_ = ecs.registry.create();
    ecs.registry.emplace<RoomTag>(entity_);
}

void Room::spawnItems() {
    auto& ecs = Services::Ecs::ref();
    for (int i = 0; i < 5; i++) {
        if (Rng::getInstance().getRandomInt(0, 100) < 50) {
            auto randomCell = *select_random(cells(), Rng::getInstance().getRandomInt(0, cells().size() - 1));

            auto& inventory = ecs.registry.get<Inventory>(randomCell);
            //                cells_.[Rng::getInstance().getRandomInt(0,
            //                cells_.size() - 1)]);
            inventory.pickUp(SwordItem::createSword());
        }
    }
}
auto Room::cells() const -> const std::set<RoomElement>& { return cells_; }
void Room::addConnector(Room::RoomConnector connector) { connectors_.insert(connector); }
auto Room::connectors() const -> const std::set<RoomConnector>& { return connectors_; }
auto Room::connectors() -> std::set<RoomConnector>& { return connectors_; }
auto Room::connector(int index) -> Room::RoomConnector { return *select_at(connectors_, index); }
auto Room::connector(int index) const -> const Room::RoomConnector& { return *select_at(connectors_, index); }
auto Room::connectorCount() const -> int { return connectors_.size(); }
bool Room::overlaps(const Room& other) const {
    //    auto& ecs = Services::Ecs::ref();
    for (const auto& cell : cells_) {
        if (other.cells_.contains(cell)) {
            return true;
        }
        //        for (const auto& otherCell : other.cells_) {
        //            if (cell.conotherCell.position.coords) {
        //                return true;
        //            }
        //        }
    }
    return false;
}
auto Room::contains(int col, int row) -> bool {
    auto& ecs = Services::Ecs::ref();
    for (const auto& cell : cells_) {
        //        if (cell.coords().col == col && cell.coords().row == row) {
        //            return true;
        //        }
        const auto& position = ecs.registry.get<Position>(cell);
        if (position.col == col && position.row == row) {
            return true;
        }
    }
    return false;
}

auto Room::get(int col, int row) -> entt::entity {
    auto& ecs = Services::Ecs::ref();
    for (const auto& cell : cells_) {
        const auto& position = ecs.registry.get<Position>(cell);
        //        spdlog::info("{} {} - {} {}\t", position.col, position.row, col, row);
        if (position.col == col && position.row == row) {
            return cell;
        }
    }
    std::runtime_error("Room does not contain cell");
    //    for (auto& cell : cells_) {
    //        if (cell.coords().col == col && cell.coords().row == row) {
    //            return cell.cell;
    //        }
    //    }
}
void Room::removeItemAt(int col, int row, entt::entity item) {
    auto& ecs = Services::Ecs::ref();
    auto cell = get(col, row);
    //    ecs.registry.destroy(cell);
    auto& inventory = ecs.registry.get<Inventory>(cell);
    inventory.removeItem(item);

    //    for (auto& cell : cells_) {
    //        if (cell.coords().col == col && cell.coords().row == row) {
    //            cell.cell.item = nullptr;
    //            return;
    //        }
    //    }
}
entt::entity Room::getItemAt(int col, int row) {
    auto& ecs = Services::Ecs::ref();
    auto cell = get(col, row);
    auto& inventory = ecs.registry.get<Inventory>(cell);

    if (inventory.items.size() == 1) {
        auto item = inventory.items.back();
        const auto name = ecs.registry.get<Named>(item).name;
        spdlog::debug("Item at {}:{} is {}", col, row, name);
        return item;
    } else
        return entt::null;
    //    for (auto& cell : cells_) {
    //        if (cell.coords().col == col && cell.coords().row == row) {
    //            if (cell.cell.item) {
    //                fmt::print("item = {}\n", cell.cell.item->name());
    //                return cell.cell.item;
    //                cell.cell.item = nullptr;
    //            }
    //        }
    //    }
    //    return nullptr;
}
auto Room::getWalkablePositions() const -> std::vector<MapPosition> {
    auto& ecs = Services::Ecs::ref();
    std::vector<MapPosition> positions;
    for (const auto& cell : cells_) {
        const auto& position = ecs.registry.get<Position>(cell);
        positions.push_back(position);
    }
    //        if (cell.cell.isWalkable()) {
    //            positions.push_back(cell.coords());
    //        }
    return positions;
}

auto Room::isWalkable(int col, int row) -> bool {
    auto& ecs = Services::Ecs::ref();
    auto cell = get(col, row);
    auto& cellInfo = ecs.registry.get<CellTag>(cell);

    return Cell::isWalkable(cellInfo.type);
    //    for (const auto& cell : cells_) {
    //        if (cell.coords().col == col && cell.coords().row == row) {
    //            return cell.cell.isWalkable();
    //        }
    //    }
    //    return false;
}

void Room::removeConnector(const Room::RoomConnector& connector) {
    auto& ecs = Services::Ecs::ref();
    //    auto cell = get(col, row);
    auto connectorInfo = ecs.registry.get<ConnectorTag>(connector);
    const auto connectorPosition = connectorInfo.position;
    // non é piú un connettore
    ecs.registry.emplace<CellTag>(connector, CellType::CELL_FLOOR);  // ma una cella
    auto& position = ecs.registry.emplace<Position>(connector);
    position.col = connectorPosition.col;
    position.row = connectorPosition.row;

    ecs.registry.emplace<Inventory>(connector);
    ecs.registry.remove<ConnectorTag>(connector);
    cells_.insert(connector);
    connectors_.erase(connector);
    //    connectors_.erase(std::remove_if(connectors_.begin(),
    //    connectors_.end(),
    //                                     [&connector](const RoomConnector& c)
    //                                     {
    //                                       return c ==
    //                                           connector;
    //                                     }),
    //                      connectors_.end());

    //    RoomElement element = {
    //        CellType::CELL_FLOOR,
    //        {connector.position().row, connector.position().col,
    //         static_cast<unsigned int>(0xffffffff)}};
    //    cells_.push_back(element);
}
void Room::removeElement(const Room::RoomElement& element) {
    cells_.insert(element);
    //    cells_.erase(std::remove_if(cells_.begin(), cells_.end(),
    //                                [&element](const RoomElement& cell) {
    //                                  return cell.position.coords ==
    //                                      element.position.coords;
    //                                }),
    //                 cells_.end());
}
