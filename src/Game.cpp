//
// Created by pollini on 10/01/2022.
//

#include "Game.h"

#include "CommandQueue.h"
#include "EventStore.h"
#include "GameCtx.h"
#include "Loaders.h"
#include "Rng.h"
#include "Services.h"
#include "easy/profiler.h"
#include "spdlog/spdlog.h"

void Game::run() {
    EASY_FUNCTION(profiler::colors::Blue800);
    spdlog::info("Game::run()");

    RexImageLoader imageLoader;
    auto img = imageLoader.load("assets/rex/test.xp")->image;

    img.flatten();

    for (int x = 0; x < img.getWidth(); x++) {
        for (int y = 0; y < img.getHeight(); y++) {
            xp::RexTile original = *img.getTile(0, x, y);
            std::cout << original.character << " ";
        }
    }

    auto& sceneManager = Services::SceneManager::ref();
    sceneManager.getCurrentScene()->onLoad();

    while (!Renderer::getInstance().shouldEnd()) {
        EASY_BLOCK("game loop");
        EASY_BLOCK("update scene");
        auto* const currentScene = sceneManager.updateSceneIfNeeded();
        EASY_END_BLOCK;

        EASY_BLOCK("handle input");
        currentScene->handleInput();
        EASY_END_BLOCK;
        EASY_BLOCK("update()");
        currentScene->update();
        EASY_END_BLOCK;
        EASY_BLOCK("render");
        // draw
        currentScene->render();
        EASY_END_BLOCK;
        EASY_END_BLOCK;
    }
}

void Game::setup(const GameOptions options) {
    Renderer::getInstance().setup();

    SetExitKey(KEY_F11);
    auto config = loadOptions();
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread%t]%v");
    //        spdlog::set_level(spdlog::level::trace);
    spdlog::info("Game setup");
    spdlog::info("Game options: {}", config.dump());
    auto& ecs = Services::Ecs::ref();
    ecs.registry.ctx().emplace<Map>();
    ecs.registry.ctx().emplace<GameOptions>(options);
    ecs.registry.ctx().emplace<EventStore>();
    ecs.registry.ctx().emplace<CommandQueue>();

    auto& sceneManager = Services::SceneManager::ref();
    sceneManager.addScene("INTRO", new IntroScene());
    sceneManager.addScene("PLAY", new PlayScene());
    sceneManager.addScene("INVENTORY", new InventoryScene());
    sceneManager.changeScene("INTRO");
}

Game::~Game() {}

json Game::loadOptions() {
    using std::filesystem::absolute;
    auto configPathAbsolute = absolute(std::filesystem::path("config"));

    auto prefabsPath = configPathAbsolute / "gameOptions.json";
    spdlog::info("Loading map prefabs config from {}", prefabsPath.string());

    std::ifstream i(prefabsPath.string());
    json config;
    i >> config;
    return config;
}
Game::Game() {
    //        GameCtx::getInstance().hero(&hero_);
    Services::Ecs::set();

    Services::SceneManager::set();
}
