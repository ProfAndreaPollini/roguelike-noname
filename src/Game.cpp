//
// Created by pollini on 10/01/2022.
//

#include "Game.h"

#include "EventStore.h"
#include "GameCtx.h"
#include "Rng.h"
#include "Services.h"
#include "spdlog/spdlog.h"

void Game::run() {
    spdlog::info("Game::run()");
    auto& sceneManager = Services::SceneManager::ref();
    sceneManager.getCurrentScene()->onLoad();

    while (!Renderer::getInstance().shouldEnd()) {
        auto* const currentScene = sceneManager.updateSceneIfNeeded();

        currentScene->handleInput();
        currentScene->update();

        // draw
        currentScene->render();
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
