//
// Created by pollini on 14/01/2022.
//

#ifndef RL_DA_ZERO_MAPPREFABS_H
#define RL_DA_ZERO_MAPPREFABS_H

#include <unordered_map>

#include "MapElement.h"
#include "MapPrefab.h"

class MapPrefabs {
   public:
    static auto getInstance() -> MapPrefabs& {
        static MapPrefabs instance;
        return instance;
    }

    void LoadConfig(const char* path);

    [[nodiscard]] const MapPrefab& getPrefab(const std::string& name) const {
        return prefabs_.at(name);
    }

    MapPrefab& getPrefab(const std::string& name) { return prefabs_.at(name); }

    [[nodiscard]] size_t size() const { return prefabs_.size(); }

    std::vector<MapPrefab> getPrefabs() const {
        std::vector<MapPrefab> prefabs;
        for (auto& [name, prefab] : prefabs_) {
            prefabs.push_back(prefab);
        }
        return prefabs;
    }

   private:
    std::unordered_map<std::string, MapPrefab> prefabs_;
};

#endif  // RL_DA_ZERO_MAPPREFABS_H
