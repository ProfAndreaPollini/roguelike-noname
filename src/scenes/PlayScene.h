//
// Created by pollini on 27/01/2022.
//

#ifndef RL_DA_ZERO_SRC_SCENES_PLAYSCENE_H
#define RL_DA_ZERO_SRC_SCENES_PLAYSCENE_H

#include "raylib-cpp.hpp"

#include "Scene.h"
#include "Map.h"
#include "util.h"
#include "Command.h"
#include "Overlay.h"

class PlayScene : public Scene {
   public:
    PlayScene();
    void update() override;
    void render() override;
    void handleInput() override;
//    ~PlayScene() override;
    void onLoad() override;

   private:
    void generateMap();
    Command* handleUserInput();
    bool waitUserInput_;

    raylib::Camera2D camera_;

    Command* cmd_ = nullptr;
    Room::RoomPtr heroRoom_;
    void handleRoomCreate(Rc<Map> map) const;
    void handleCameraMovement();
    std::vector<Rc<Overlay>> overlays_;
};

#endif  // RL_DA_ZERO_SRC_SCENES_PLAYSCENE_H
