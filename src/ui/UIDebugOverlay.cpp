//
// Created by pollini on 28/01/2022.
//

#include "UIDebugOverlay.h"

#include "raylib-cpp.hpp"

void UIDebugOverlay::draw() const {
    auto fps = GetFPS();
    //        auto fps = profiler::main_thread_frameTime();
    raylib::DrawText(TextFormat("FPS: %d", fps), 10, 10, 20, LIGHTGRAY);
}
