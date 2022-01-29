//
// Created by pollini on 10/01/2022.
//

#include "spdlog/spdlog.h"

#include "Game.h"

#include "GameCtx.h"
#include "Rng.h"

void Game::run() {
    spdlog::info("Game::run()");

    SceneManager::getInstance().getCurrentScene()->onLoad();

    while (!Renderer::getInstance().shouldEnd()) {
        auto* const currentScene =
            SceneManager::getInstance().updateSceneIfNeeded();

        currentScene->handleInput();
        currentScene->update();

        // draw
        currentScene->render();
    }
}

void Game::setup(const GameOptions& options) {
    Renderer::getInstance().setup();
    SetExitKey(KEY_F11);
    auto config = loadOptions();
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread%t]%v");
    //        spdlog::set_level(spdlog::level::trace);
    spdlog::info("Game setup");
    spdlog::info("Game options: {}", config.dump());
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
