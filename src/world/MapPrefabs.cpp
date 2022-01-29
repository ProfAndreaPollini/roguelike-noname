//
// Created by pollini on 14/01/2022.
//

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include "fmt/core.h"
// for convenience
using json = nlohmann::json;

#include "MapPrefab.h"
#include "MapPrefabs.h"
#include "raylib-cpp.hpp"

void MapPrefabs::LoadConfig(const char* configPath) {
    using std::filesystem::absolute;
    auto configPathAbsolute = absolute(std::filesystem::path(configPath));
    fmt::print("Loading map prefabs config from {}\n",
               configPathAbsolute.string());

    auto prefabsPath = configPathAbsolute / "prefabs.json";
    fmt::print("Loading prefabs from {}\n", prefabsPath.string());
    std::ifstream i(prefabsPath.string());
    json config;
    i >> config;

    //    fmt::print("{}\n", config.dump(4).c_str());
    fmt::print("test  ={}\n", config["test"]);

    for (auto prefab : config["prefabs"]) {
        auto prefabName = prefab["name"];
        auto prefabPath = configPathAbsolute / "prefabs" / prefab["path"];
        fmt::print("Loading prefab {} from {}\n", prefabName,
                   prefabPath.string());
        fmt::print("prefab ={}\n", prefab.dump(4).c_str());

        raylib::Image prefabImage =
            raylib::LoadImage(prefabPath.string().c_str());

        MapPrefab prefabElement;

        for (int row = 0; row < prefabImage.height; ++row) {
            for (int col = 0; col < prefabImage.width; ++col) {
                raylib::Color pixel = GetImageColor(prefabImage, col, row);
                auto pixelCode = (unsigned int)pixel.ToInt();

                if (pixelCode == 0xff00ffff) {
                    prefabElement.addConnector(row, col, Direction::NORTH);
                } else if (pixelCode == 0x00ff00ff) {
                    prefabElement.addConnector(row, col, Direction::WEST);
                } else if (pixelCode == 0xff0000ff) {
                    prefabElement.addConnector(row, col, Direction::EAST);
                } else if (pixelCode == 0x0000ffff) {
                    prefabElement.addConnector(row, col, Direction::SOUTH);
                }

                if (pixelCode == 0xffffffff) {
                    prefabElement.addCell(row, col, pixelCode);
                } else if (pixelCode == 0x000000ff) {
                    prefabElement.addCell(row, col, pixelCode);
                }
                //                     else {
                //                         fmt::print(" connector color:
                //                         ({},{},{} |
                //                         {})\n",pixel.r,pixel.g,pixel.b,pixel.a);
                //                        fmt::print("connettore ({0:x}) at
                //                        ({1},{2})\n", pixelCode,row,col);
                //                    }
            }
        }
        fmt::print("<MapElement(cells:{})>", prefabElement.cells().size());
        for (auto cell : prefabElement.cells()) {
            fmt::print("({0},{1}) -> {2:x}\t", cell.coords.row, cell.coords.col,
                       cell.value);
        }
        fmt::print("\n");
        for (auto cell : prefabElement.connectors()) {
            const char* value;
            switch (cell.direction()) {
                case Direction::NORTH:
                    value = "N";
                    break;
                case Direction::WEST:
                    value = "W";
                    break;
                case Direction::EAST:
                    value = "E";
                    break;
                case Direction::SOUTH:
                    value = "S";
                    break;
            }
            fmt::print("({0},{1}) -> {2}\t", cell.position().row,
                       cell.position().col, value);
        }
        fmt::print("baricenter (r={0},c={1})\n", prefabElement.baricenter().row,
                   prefabElement.baricenter().col);
        fmt::print("\n<MapElement/>\n");

        prefabs_.insert({prefabName, prefabElement});
    }
}