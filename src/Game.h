//
// Created by pollini on 10/01/2022.
//

#ifndef RL_DA_ZERO_GAME_H
#define RL_DA_ZERO_GAME_H

#include <memory>

#include "Renderer.h"
#include "Hero.h"
#include "GameState.h"
#include "PlayerTurn.h"
#include "world/Map.h"
#include "scenes/Scene.h"
#include "util.h"
#include "PlayScene.h"
#include "GameCtx.h"
#include "IntroScene.h"
#include "SceneManager.h"

struct GameOptions {
    int width;
    int height;
    const char *title;

    GameOptions() : width(80), height(50), title("RL-DA-Zero") {}

};

class Game {
public:
    Game() : renderer_(&Renderer::getInstance())  {
        GameCtx::getInstance().hero( &hero_ );
        SceneManager::getInstance().addScene( "INTRO",std::make_shared<IntroScene>() );
        SceneManager::getInstance().addScene( "PLAY",std::make_shared<PlayScene>() );
        SceneManager::getInstance().changeScene( "INTRO" );
    }
    void setup(const GameOptions& options = GameOptions());
    void run();

    bool processInput();
    void update();

    ~Game();
private:
    std::unique_ptr<Renderer> renderer_;
    bool waitUserInput_ = true;
    Hero hero_;
    std::unique_ptr<GameState> state_{new PlayerTurn()};

    Ptr<Scene> scene_{new IntroScene()};
//    Map* map_;
};


#endif //RL_DA_ZERO_GAME_H
