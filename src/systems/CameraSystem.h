//
// Created by pollini on 02/02/2022.
//

#ifndef RL_DA_ZERO_SRC_SYSTEMS_CAMERASYSTEM_H
#define RL_DA_ZERO_SRC_SYSTEMS_CAMERASYSTEM_H

struct CameraSystem {
    [[maybe_unused]] static void updateCamera(int row, int col);
    static void updateViewport();
    static void createCamera(int row, int col, int width, int height);
};

#endif  // RL_DA_ZERO_SRC_SYSTEMS_CAMERASYSTEM_H
