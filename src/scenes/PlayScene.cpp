//
// Created by pollini on 27/01/2022.
//

#include "PlayScene.h"

#include <easy/profiler.h>
#include <spdlog/fmt/chrono.h>
#include <spdlog/stopwatch.h>
using std::chrono::duration_cast;
using std::chrono::milliseconds;

#include "CameraSystem.h"
#include "Game.h"
#include "GameCtx.h"
#include "HeroSystem.h"
#include "LogOverlay.h"
#include "MapAlgorithms.h"
#include "MapPrefabs.h"
#include "MoveCommand.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Services.h"
#include "StatsOverlay.h"
#include "Systems.h"
#include "UIDebugOverlay.h"
#include "WorldBuilder.h"
#include "generators/EntitySpawner.h"
#include "raylib-cpp.hpp"
void PlayScene::handleInput() {
    auto& ecs = Services::Ecs::ref();

    auto& map = ecs.registry.ctx().at<Map>();
    //    auto map = GameCtx::getInstance().map();

    if (waitUserInput_) {
        cmd_ = handleUserInput();

        if (cmd_ != nullptr) {
            waitUserInput_ = false;
        }
    }

    if (IsKeyPressed(KEY_F)) {
        handleRoomCreate(map);
    }

    if (IsKeyDown(KEY_G)) {
        cellInfoSystem_->run(camera_);
    }

    handleCameraMovement();
}

void PlayScene::handleRoomCreate(Map& map) const {
    int attempts = 0;
    auto otherPrefabIndex = 0;
    MapPrefab otherPrefab;

    std::vector<MapPrefab> mapElements = MapPrefabs::getInstance().getPrefabs();

    while (attempts < 10) {
        if (attempts == 0) {
            otherPrefabIndex = Rng::getInstance().getRandomInt(0, mapElements.size() - 1);

            otherPrefab = mapElements[otherPrefabIndex];
        }
        auto roomIdx = Rng::getInstance().getRandomInt(0, map.roomWithConnectionCount() - 1);
        auto added = map.addPrefabTo(roomIdx, otherPrefab);
        if (added) {
            fmt::print("Added prefab to room {}\n", roomIdx);
            fmt::print("rooms = {}\n", map.roomCount());
            attempts = 0;
            break;
        } else {
            fmt::print(".");
            attempts++;
        }
    }
}

void PlayScene::update() {
    if (!waitUserInput_) {
        HeroSystem::updateHero();
        worldUpdateSystem_.update();
        //        auto hero = GameCtx::getInstance().hero();
        auto& ecs = Services::Ecs::ref();

        auto& map = ecs.registry.ctx().at<Map>();

        //        auto map = GameCtx::getInstance().map();
        //        drawUiInfo.messages.clear();
        //        cmd_->execute(hero.get(), map);
        auto hero = ecs.registry.view<HeroTag>().front();
        const auto& position = ecs.registry.get<Position>(hero);

        camera_.target.x = position.col * Renderer::getInstance().getTileSize().x;
        camera_.target.y = position.row * Renderer::getInstance().getTileSize().y;

        heroRoom_ = map.queryRoom(position.col, position.row);
        if (!heroRoom_->visited()) {
            heroRoom_->setVisited(true);
        }
        //        delete cmd_;

        waitUserInput_ = true;
    }
}

void PlayScene::render() {
    EASY_FUNCTION();
    //    spdlog::info("PlayScene::render");

    Renderer::getInstance().prepare();

    auto& ecs = Services::Ecs::ref();
    //    spdlog::info("Prepare time {}", duration_cast<milliseconds>(sw.elapsed()));
    const auto& map = ecs.registry.ctx().at<Map>();

    auto hero = ecs.registry.view<HeroTag>().front();
    const auto& position = ecs.registry.get<Position>(hero);

    //    auto zeroWorld = camera_.GetScreenToWorld({0, 0});
    //    auto bottomLeft = camera_.GetScreenToWorld({1920, 1080});
    //    spdlog::info("camera top left: {},{}", zeroWorld.x, zeroWorld.y);

    //    raylib::Vector2 mousePos = GetMousePosition();
    //    auto mouseWorld = camera_.GetScreenToWorld(mousePos);
    //    raylib::DrawText(TextFormat("Mouse: %f, %f", mouseWorld.x, mouseWorld.y), mousePos.x + 20, mousePos.y + 30,
    //    20,
    //                     LIGHTGRAY);

    updateCamera();

    BeginMode2D(camera_);

    mapRenderSystem_->updateCamera(&viewport_);
    mapRenderSystem_->render(heroRoom_->id());

    renderDoorsSystem(heroRoom_);
    //    spdlog::info("doors draw {}", duration_cast<milliseconds>(sw.elapsed()));
    Renderer::getInstance().drawText("@", position.col, position.row, {255, 255, 255, 255});
    renderMonsterSystem(heroRoom_);
    //    spdlog::info("monsters draw {}", duration_cast<milliseconds>(sw.elapsed()));
    //        renderer_->drawRays(heroRoom, hero_);
    if (display_astar_) {
        Renderer::getInstance().drawAstar(astar_);
    }


    EndMode2D();
    //    Renderer::getInstance().drawUi(drawUiInfo);
    for (const auto& overlay : overlays_) {
        overlay->draw();
    }
    Renderer::getInstance().draw();
    //    spdlog::info("render time {}", duration_cast<milliseconds>(sw.elapsed()));
}

PlayScene::PlayScene() : waitUserInput_(true), alreadyStarted_(false) {
    //    raylib::Camera2D camera{};

    // create hero
    Hero::createHero();

    auto& ecs = Services::Ecs::ref();

    auto& options = ecs.registry.ctx().at<GameOptions>();

    auto debugUi = new UIDebugOverlay();
    overlays_.push_back(std::shared_ptr<UIDebugOverlay>(debugUi));

    auto logUi = new LogOverlay({(float)options.width - 300, 0}, {300, 400.0f});
    overlays_.push_back(std::shared_ptr<LogOverlay>(logUi));

    auto statsUI = new StatsOverlay({(float)options.width - 300, 400.0f}, {300, 150.0f});
    overlays_.push_back(std::shared_ptr<StatsOverlay>(statsUI));
}

void PlayScene::onLoad() {
    if (!alreadyStarted_) {
        mapRenderSystem_.reset(new MapRendererSystem());
        cellInfoSystem_.reset(new CellInfoSystem());
        generateMap();
        alreadyStarted_ = true;
    }
    auto& ecs = Services::Ecs::ref();

    auto hero = ecs.registry.view<HeroTag>().front();
    const auto& position = ecs.registry.get<Position>(hero);

    //    auto hero = GameCtx::getInstance().hero();

    camera_.offset =
        (Vector2){50 * Renderer::getInstance().getTileSize().x, 30 * Renderer::getInstance().getTileSize().y};
    camera_.target.x = position.col * Renderer::getInstance().getTileSize().x;
    camera_.target.y = position.row * Renderer::getInstance().getTileSize().y;
    camera_.rotation = 0.0f;
    camera_.zoom = 1.5f;
    updateCamera();
}
void PlayScene::updateCamera() {
    // get world position of the 0,0 point
    auto zeroWorld = camera_.GetScreenToWorld({0, 0});
    // get bottomright position of the screen
    auto bottomLeft = camera_.GetScreenToWorld({1920, 1080});
    viewport_.x = zeroWorld.x / Renderer::getInstance().getTileSize().x;
    viewport_.y = zeroWorld.y / Renderer::getInstance().getTileSize().y;
    viewport_.width = (bottomLeft.x - zeroWorld.x) / Renderer::getInstance().getTileSize().x;
    viewport_.height = (bottomLeft.y - zeroWorld.y) / Renderer::getInstance().getTileSize().y;
}
void PlayScene::generateMap() {
    WorldBuilder worldBuilder;
    worldBuilder.setup();

    auto& ecs = Services::Ecs::ref();

    hero_ = ecs.registry.view<HeroTag>().front();
    auto& position = ecs.registry.get<Position>(hero_);

    position = worldBuilder.startingPoint();
    heroRoom_ = worldBuilder.startingRoom();

    CameraSystem::createCamera(position.col, position.row, 50, 20);
    CameraSystem::updateViewport();

    for (int i = 0; i < 15; i++) worldBuilder.addRoom();
    worldBuilder.build();

    MonsterSpawner monsterSpawner;
    monsterSpawner.spawn();

    ItemSpawner itemSpawner;
    itemSpawner.spawn();

    DoorAndKeysSpawner doorAndKeysSpawner{8};
    doorAndKeysSpawner.spawn();
}

Rc<Command> PlayScene::handleUserInput() {
    Rc<Command> cmd;
    if (IsKeyPressed(KEY_LEFT)) {
        cmd.reset(new MoveCommand(hero_, -1, 0));
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        cmd.reset(new MoveCommand(hero_, 1, 0));
    }
    if (IsKeyPressed(KEY_UP)) {
        cmd.reset(new MoveCommand(hero_, 0, -1));
    }
    if (IsKeyPressed(KEY_DOWN)) {
        cmd.reset(new MoveCommand(hero_, 0, 1));
    }
    if (IsKeyPressed(KEY_I)) {
        auto& sceneManager = Services::SceneManager::ref();
        sceneManager.changeScene("INVENTORY");
        return nullptr;
    }
    //    auto& ecs = Services::Ecs::ref();

    //    auto hero = ecs.registry.view<HeroTag>().front();

    //    auto& actions = ecs.registry.get<Actions>(hero);
    //    if (cmd) {
    //        actions.push_back(cmd);
    //    }

    // send command to the command queue
    if (cmd) {
        pushCommand(cmd);
    }

    if (IsKeyPressed(KEY_F7)) {
        if (display_astar_ == false) {
            astar_.updateFromMap();

            auto& ecs = Services::Ecs::ref();

            auto hero = ecs.registry.view<HeroTag>().front();
            auto& position = ecs.registry.get<Position>(hero);
            //            auto hero = GameCtx::getInstance().hero();

            astar_.setup(MapPosition::fromRowCol(position.row, position.col), astar_.positions()[0]);
            astar_.findPath();
            display_astar_ = true;
        }
        // astar_->updateFromRoom(0, 0);
        // display_astar_ = true;
    }

    if (IsKeyPressed(KEY_F8)) {
        if (display_astar_ == true) {
            display_astar_ = false;
        }
        // astar_->updateFromRoom(0, 0);
        // display_astar_ = true;
    }
    return cmd;
}

void PlayScene::handleCameraMovement() {
    if (IsKeyPressed(KEY_W)) {
        camera_.target.y = camera_.target.y - 50;
    }
    if (IsKeyPressed(KEY_S)) {
        camera_.target.y = camera_.target.y + 50;
    }
    if (IsKeyPressed(KEY_A)) {
        camera_.target.x = camera_.target.x - 50;
    }
    if (IsKeyPressed(KEY_D)) {
        camera_.target.x = camera_.target.x + 50;
    }

    // Camera zoom controls
    camera_.zoom += GetMouseWheelMove() * 0.05f;

    if (camera_.zoom > 3.0f)
        camera_.zoom = 3.0f;
    else if (camera_.zoom < 0.1f)
        camera_.zoom = 0.1f;
}
