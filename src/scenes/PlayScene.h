//
// Created by pollini on 27/01/2022.
//

#ifndef RL_DA_ZERO_SRC_SCENES_PLAYSCENE_H
#define RL_DA_ZERO_SRC_SCENES_PLAYSCENE_H

#include "CellInfoSystem.h"
#include "Command.h"
#include "Map.h"
#include "MapAlgorithms.h"
#include "MapRendererSystem.h"
#include "Overlay.h"
#include "Scene.h"
#include "Services.h"
#include "WorldUpdateSystem.h"
#include "components/Viewport.h"
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
    WorldUpdateSystem worldUpdateSystem_;
    entt::entity hero_;

    std::vector<Rc<Overlay>> overlays_;
    bool display_astar_;
    Rc<MapRendererSystem> mapRenderSystem_;
    Rc<CellInfoSystem> cellInfoSystem_;
    Viewport viewport_;
    void updateCamera();
};

#endif  // RL_DA_ZERO_SRC_SCENES_PLAYSCENE_H
