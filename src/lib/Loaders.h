//
// Created by pollini on 10/02/2022.
//

#ifndef RL_DA_ZERO_SRC_LIB_LOADERS_H
#define RL_DA_ZERO_SRC_LIB_LOADERS_H

#include <spdlog/spdlog.h>

#include <filesystem>

#include "REXSpeeder.h"
#include "entt/entt.hpp"

struct RexImageResource {
    xp::RexImage image;
};

struct RexImageLoader : entt::resource_loader<RexImageLoader, RexImageResource> {
    std::shared_ptr<RexImageResource> load(std::filesystem::path filePath) const {
        using std::filesystem::absolute;
        auto filePathAbsolute = absolute(filePath);
        spdlog::info("Loading image {}", filePathAbsolute.string());
        xp::RexImage image{filePathAbsolute.string()};

        return std::shared_ptr<RexImageResource>(new RexImageResource{image});
    }
};
#endif  // RL_DA_ZERO_SRC_LIB_LOADERS_H
