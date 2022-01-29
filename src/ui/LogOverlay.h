//
// Created by pollini on 28/01/2022.
//

#ifndef RL_DA_ZERO_SRC_UI_LOGOVERLAY_H
#define RL_DA_ZERO_SRC_UI_LOGOVERLAY_H

#include "raylib-cpp.hpp"

#include "Overlay.h"

class LogOverlay : public Overlay{
public:
    LogOverlay(raylib::Vector2 position, raylib::Vector2 size) : Overlay(position,size) {}
    ~LogOverlay() override = default;

    void draw() const override {
        DrawRectangle(position_.x, position_.y, size_.x, size_.y, bgColor_);
        raylib::DrawText(TextFormat("LOG"), position_.x+10, position_.y+10, 20, GREEN);
    }



   private:
    raylib::Color bgColor_ = raylib::Color{200,200,200,128};
};

#endif  // RL_DA_ZERO_SRC_UI_LOGOVERLAY_H
