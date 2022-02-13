//
// Created by pollini on 28/01/2022.
//

#ifndef RL_DA_ZERO_SRC_UI_UIDEBUGOVERLAY_H
#define RL_DA_ZERO_SRC_UI_UIDEBUGOVERLAY_H

#include "Overlay.h"
#include "easy/profiler.h"
#include "extras/raygui.h"

class UIDebugOverlay : public Overlay {
   public:
    UIDebugOverlay() : Overlay({0, 0}, {0, 0}) {}

    ~UIDebugOverlay() override = default;

    void draw() const override;
};

#endif  // RL_DA_ZERO_SRC_UI_UIDEBUGOVERLAY_H
