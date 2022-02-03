//
// Created by pollini on 27/01/2022.
//

#ifndef RL_DA_ZERO_SRC_SCENES_PLAYSCENE_H
#define RL_DA_ZERO_SRC_SCENES_PLAYSCENE_H

#include "Command.h"
#include "Map.h"
#include "MapAlgorithms.h"
#include "Overlay.h"
#include "Scene.h"
#include "Services.h"
#include "raylib-cpp.hpp"
#include "util.h"

class PlayScene : public Scene {
   public:
    PlayScene();
    void update() override;
    void render() override;
    void handleInput() override;

    void onLoad() override;

   private:
    void generateMap();
    auto handleUserInput() -> Rc<Command>;

    void handleRoomCreate(Map& map) const;
    void handleCameraMovement();

    bool waitUserInput_;
    bool alreadyStarted_;

    raylib::Camera2D camera_;

    Rc<Command> cmd_ = nullptr;
    Room::RoomPtr heroRoom_;
    AStar astar_;

    std::vector<Rc<Overlay>> overlays_;
    bool display_astar_;
};

#endif  // RL_DA_ZERO_SRC_SCENES_PLAYSCENE_H
