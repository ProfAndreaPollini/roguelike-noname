//
// Created by pollini on 28/01/2022.
//

#ifndef RL_DA_ZERO_SRC_UI_OVERLAY_H
#define RL_DA_ZERO_SRC_UI_OVERLAY_H

#include "raylib-cpp.hpp"

class Overlay {
   public:
    Overlay(raylib::Vector2 position, raylib::Vector2 size)
        : position_(position), size_(size) {}
    auto getPosition() -> raylib::Vector2 { return position_; }

    virtual ~Overlay() = default;

    virtual void draw() const = 0;

   protected:
    raylib::Vector2 position_;
    raylib::Vector2 size_;
};

#endif  // RL_DA_ZERO_SRC_UI_OVERLAY_H
