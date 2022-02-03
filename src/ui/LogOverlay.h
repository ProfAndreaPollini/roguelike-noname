//
// Created by pollini on 28/01/2022.
//

#ifndef RL_DA_ZERO_SRC_UI_LOGOVERLAY_H
#define RL_DA_ZERO_SRC_UI_LOGOVERLAY_H

#include "Overlay.h"
#include "raylib-cpp.hpp"

class LogOverlay : public Overlay {
   public:
    LogOverlay(raylib::Vector2 position, raylib::Vector2 size)
        : Overlay(position, size) {}
    ~LogOverlay() override = default;

    void draw() const override;

   private:
    raylib::Color bgColor_ = raylib::Color{200, 200, 200, 100};
};

#endif  // RL_DA_ZERO_SRC_UI_LOGOVERLAY_H
