//
// Created by pollini on 22/01/2022.
//

#ifndef RL_DA_ZERO_MAPPREFAB_H
#define RL_DA_ZERO_MAPPREFAB_H

#include <vector>

#include "fmt/core.h"
#include "MapElement.h"


class MapPrefab {
public:
    virtual ~MapPrefab() = default;

     void addCell(int row, int col, unsigned int value) {
        MapElementCell cell{row, col, value};
        cells_.push_back(cell);
    }

    MapPrefab() = default;
    MapPrefab(const MapPrefab &other) {
        std::copy(other.cells_.begin(), other.cells_.end(), std::back_inserter(cells_));
        std::copy(other.connectors_.begin(), other.connectors_.end(), std::back_inserter(connectors_));
        selectedConnector_ = other.selectedConnector_;
    }

    void addConnector(int row, int col, Direction direction) {
        MapElementConnector cell{row, col, direction};
        connectors_.push_back(cell);
    }


    [[maybe_unused]] std::vector<MapElementConnector> connectors() const  {
            return connectors_;
    }

    std::vector<MapElementCell> cells() const  {
            return cells_;
    }


    MapPosition  baricenter() const {
        int row = 0;
        int col = 0;
        for (auto cell : cells_) {
            row += cell.coords.row;
            col += cell.coords.col;
        }
        return {static_cast<int>(row / cells_.size()), static_cast<int>(col / cells_.size())};
    }

    void setTranslation(MapPosition translation) {
        setTranslation(translation.row, translation.col);
    }

    void setTranslation(int row, int col) {
        translation_ = {row, col};
       const auto connectorCoords = connectors_[selectedConnector_].position();
        for (auto&cell :cells_) {
            cell.coords -= connectorCoords;
            cell.coords += translation_;
        }


        for (auto& connector : connectors_) {
//            MapElementConnector rotatedConnector = connector;
            connector -= connectorCoords;
            connector += translation_;
        }
    }



    void debug() {
        fmt::print("translation: {} {}\n", translation_.row, translation_.col);
        fmt::print("rotation: {}\n", rotation_);
        fmt::print("connectors: {}\n", connectors_.size());
        for (auto &connector : connectors()) {
            fmt::print("{} {} {}\n", connector.position().row, connector.position().col, static_cast<int>(connector.direction()));
        }
        fmt::print("cells: {}\n", cells_.size());
        for (auto &cell : cells()) {
            fmt::print("({} {}) ", cell.coords.row, cell.coords.col);
        }
        fmt::print("\n");
    }

    void debugConnectors() {
        fmt::print("connectors: {}\n", connectors_.size());
        for (auto &connector : connectors()) {
            fmt::print("({} {}) {}\n", connector.position().row, connector.position().col, static_cast<int>(connector.direction()));
        }
    }

    void rotateRight() {
        rotation_ = (rotation_ + 1) % 4;
        const auto connectorCoords = connectors_[selectedConnector_].position();

        for (auto&cell :cells_) {
            cell.coords -= connectorCoords;
            cell.coords.rotateRight(1);
            cell.coords += connectorCoords;
        }

        for (auto& connector : connectors_) {

            connector -= connectorCoords;
            connector.rotatePositionRight();
            connector += connectorCoords;
            connector.setDirection(rotateDirection(connector.direction(), 1));
        }
    }

    void centerToConnectorPosition(int index) {
        if (index >= connectors_.size()) {
            throw std::runtime_error("index out of range");
        }
        selectedConnector_ = index;
//        setTranslation(connectors_[index].coords);
    }

    void selectRandomConnector() {
        std::uniform_int_distribution<int> uni(0, connectors_.size() - 1);
        selectedConnector_ = std::rand() % connectors_.size();
    }

    MapPosition selectedConnectorCoords() {

        return connectors_[selectedConnector_].position();
    }
    Direction selectedConnectorDirection() {
        return connectors_[selectedConnector_].direction();
    }

    MapElementConnector selectedConnector() {
        return connectors_[selectedConnector_];
    }

    void removeSelectedConnector() {
        auto connector = connectors_[selectedConnector_];
        fmt::print("removing connector {} {}\n", connector.position().row, connector.position().col);
        cells_.push_back(MapElementCell{connector.position().row,connector.position().col, 0xffffffff});
        connectors_.erase(connectors_.begin() + selectedConnector_);
        selectedConnector_ = 0;
    }

    bool overlaps(const MapPrefab& other) const {
        for (const auto& cell : cells()) {
            for (const auto& c:other.cells()) {

                if (c.coords.row == cell.coords.row && c.coords.col == cell.coords.col) {
                    fmt::print("overlaps\n");

                    return true;
                }
            }
        }
        return false;
    }




    bool merge(MapPrefab& other) {


        while(!isDirectionFacing(selectedConnectorDirection(), other.selectedConnectorDirection())) {
            other.rotateRight();
            other.debugConnectors();
            debugConnectors();
        }


        auto selectedConnectorPos = selectedConnectorCoords();
        auto selectedConnectorDir = selectedConnectorDirection();
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
        other.setTranslation(selectedConnectorPos);

        if (overlaps(other)) {

        fmt::print("overlaps\n");
            return false;
        }

//        debug();
//        other.debug();

        removeSelectedConnector();
        other.removeSelectedConnector();

        for (auto cell : other.cells()) {
            cells_.push_back(cell);
        }
        for (auto cell : other.connectors()) {
            connectors_.push_back(cell);
        }
        return true;
    }

private:
    std::vector<MapElementConnector> connectors_{};
    std::vector<MapElementCell> cells_{};
//    Direction direction_ = Direction::NORTH;
    MapCoord translation_ = {0, 0};
    int rotation_ = 0;
    int selectedConnector_ = 0;
};

#include "MapElement.h"
#include "MapPosition.h"

#endif //RL_DA_ZERO_MAPPREFAB_H
