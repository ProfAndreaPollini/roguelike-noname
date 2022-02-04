//
// Created by pollini on 27/01/2022.
//

#include "PlayScene.h"

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
#include "UIDebugOverlay.h"

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
        //        delete cmd_;

        waitUserInput_ = true;
    }
}

void PlayScene::render() {
    Renderer::getInstance().prepare();

    auto& ecs = Services::Ecs::ref();

    auto& map = ecs.registry.ctx().at<Map>();

    //        auto map = GameCtx::getInstance().map();
    //        drawUiInfo.messages.clear();
    //        cmd_->execute(hero.get(), map);
    auto hero = ecs.registry.view<HeroTag>().front();
    const auto& position = ecs.registry.get<Position>(hero);

    //    auto map = GameCtx::getInstance().map();

    BeginMode2D(camera_);

    map.draw(heroRoom_);
    Renderer::getInstance().drawEntity({position.col, position.row, "@"});
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
}

PlayScene::PlayScene() : waitUserInput_(true), alreadyStarted_(false) {
    //    raylib::Camera2D camera{};

    // create hero
    Hero::createHero();

    auto& ecs = Services::Ecs::ref();

    auto& options = ecs.registry.ctx().at<GameOptions>();

    auto debugUi = new UIDebugOverlay();
    overlays_.push_back(std::shared_ptr<UIDebugOverlay>(debugUi));

    auto logUi = new LogOverlay({(float)options.width - 300, 0}, {300, (float)options.height});
    overlays_.push_back(std::shared_ptr<LogOverlay>(logUi));
}

void PlayScene::onLoad() {
    if (!alreadyStarted_) {
        generateMap();
        alreadyStarted_ = true;
        //        auto roomconnections =
        //            GameCtx::getInstance().map()->roomConnectionsBFS();
        //        spdlog::info("Room connections: {}", roomconnections.size());
        //        for (const auto& rc : roomconnections) {
        //            spdlog::info("{}    ", rc);
        //        }
    }
    auto& ecs = Services::Ecs::ref();

    auto& map = ecs.registry.ctx().at<Map>();

    //        auto map = GameCtx::getInstance().map();
    //        drawUiInfo.messages.clear();
    //        cmd_->execute(hero.get(), map);
    auto hero = ecs.registry.view<HeroTag>().front();
    const auto& position = ecs.registry.get<Position>(hero);

    //    auto hero = GameCtx::getInstance().hero();

    camera_.offset =
        (Vector2){25 * Renderer::getInstance().getTileSize().x, 10 * Renderer::getInstance().getTileSize().y};
    camera_.target.x = position.col * Renderer::getInstance().getTileSize().x;
    camera_.target.y = position.row * Renderer::getInstance().getTileSize().y;
    camera_.rotation = 0.0f;
    camera_.zoom = 1.0f;
}
void PlayScene::generateMap() {
    MapPrefabs::getInstance().LoadConfig("config");

    auto prefab = MapPrefabs::getInstance().getPrefab("prefab3");
    auto prefab2 = MapPrefabs::getInstance().getPrefab("prefab2");
    auto prefab3 = MapPrefabs::getInstance().getPrefab("prefab4");

    std::vector<MapPrefab> mapElements = MapPrefabs::getInstance().getPrefabs();

    prefab.centerToConnectorPosition(0);
    prefab2.centerToConnectorPosition(0);
    prefab3.centerToConnectorPosition(0);

    auto& ecs = Services::Ecs::ref();

    auto hero = ecs.registry.view<HeroTag>().front();
    auto& position = ecs.registry.get<Position>(hero);
    auto& map = ecs.registry.ctx().at<Map>();

    auto rooms = 0;
    auto attempts = 0;
    auto currentPrefabIndex = Rng::getInstance().getRandomInt(0, mapElements.size() - 1);
    auto currentPrefab = mapElements[currentPrefabIndex];
    currentPrefab.setTranslation(100, 100);

    //    hero->set(currentPrefab.baricenter().col,
    //    currentPrefab.baricenter().row);
    position.col = currentPrefab.baricenter().col;
    position.row = currentPrefab.baricenter().row;

    CameraSystem::createCamera(position.col, position.row, 50, 20);
    CameraSystem::updateViewport();

    std::shared_ptr<Room> currentRoom = Room::createFromMapElement(currentPrefab);

    //    Graph<Room> graph{currentRoom};

    auto r = Room::createFromMapElement(currentPrefab);
    heroRoom_ = r;
    map.addRoom(r);

    //    auto walkable = r->getWalkablePositions();

    //    DijkstraMap dm(walkable);
    //    dm.run(walkable[0]);
    //    Astar astar(walkable);

    for (int i = 0; i < 15; i++) handleRoomCreate(map);
}

Rc<Command> PlayScene::handleUserInput() {
    Rc<Command> cmd;
    if (IsKeyPressed(KEY_LEFT)) {
        cmd.reset(new MoveCommand(-1, 0));
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        cmd.reset(new MoveCommand(1, 0));
    }
    if (IsKeyPressed(KEY_UP)) {
        cmd.reset(new MoveCommand(0, -1));
    }
    if (IsKeyPressed(KEY_DOWN)) {
        cmd.reset(new MoveCommand(0, 1));
    }
    if (IsKeyPressed(KEY_I)) {
        auto& sceneManager = Services::SceneManager::ref();
        sceneManager.changeScene("INVENTORY");
        return nullptr;
    }
    auto& ecs = Services::Ecs::ref();

    auto hero = ecs.registry.view<HeroTag>().front();

    auto& actions = ecs.registry.get<Actions>(hero);
    if (cmd) {
        actions.push_back(cmd);
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
