//
// Created by pollini on 21/01/2022.
//

#include "Room.h"
#include "MapPrefab.h"

Room::RoomPtr Room::createFromMapElement(MapPrefab &mapElement) {
    auto room = std::make_shared<Room>();
//        room->mapElement_ = mapElement;
    for(auto &cell : mapElement.cells()) {
        Cell c{CellType::CELL_WALL};
        if (cell.value == 0xffffffff) {
            c.type = CellType::CELL_FLOOR;
        }
        RoomElement roomElement{c, cell};
        room->cells().push_back(roomElement); //.push_back({c,cell.coords});
    }

    for(auto&connector: mapElement.connectors()) {
        room->addConnector(connector);
    }

    return room;
}
