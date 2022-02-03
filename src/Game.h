//
// Created by pollini on 10/01/2022.
//

#ifndef RL_DA_ZERO_GAME_H
#define RL_DA_ZERO_GAME_H

#include <filesystem>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

#include "GameCtx.h"
#include "GameState.h"
#include "Hero.h"
#include "IntroScene.h"
#include "InventoryScene.h"
#include "PlayScene.h"
#include "PlayerTurn.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Services.h"
#include "scenes/Scene.h"
#include "util.h"
#include "world/Map.h"

struct GameOptions {
    int width;
    int height;
    const char* title;
    const char* font;

    GameOptions() : width(1920), height(1080), title("noname RL"), font("") {}
};

class Game {
   public:
    Game();
    void setup(const GameOptions options = GameOptions());
    void run();

    ~Game();

   private:
    json loadOptions();
};

#endif  // RL_DA_ZERO_GAME_H
