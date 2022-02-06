//
// Created by pollini on 06/02/2022.
//

#ifndef RL_DA_ZERO_SRC_UI_STATSOVERLAY_H
#define RL_DA_ZERO_SRC_UI_STATSOVERLAY_H

#include "Overlay.h"

class StatsOverlay : public Overlay {
   public:
    StatsOverlay(raylib::Vector2 position, raylib::Vector2 size)
        : Overlay(position, size) {}
    ~StatsOverlay() override = default;

    void draw() const override;

   private:
    raylib::Color bgColor_ = raylib::Color{200, 200, 200, 100};
};

#endif  // RL_DA_ZERO_SRC_UI_STATSOVERLAY_H
