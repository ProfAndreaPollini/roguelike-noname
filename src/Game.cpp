//
// Created by pollini on 10/01/2022.
//

#include "Game.h"

#include <memory>

#include "GameCtx.h"
#include "Graph.h"
#include "MapPrefab.h"
#include "MapPrefabs.h"
#include "Rng.h"
#include "Room.h"
#include "fmt/core.h"

void Game::run() {
    fmt::print("Game running...\n");
    //    Command* cmd = nullptr;
    //    DrawUIInfo drawUiInfo;
    //    Room::RoomPtr heroRoom;

    scene_->onLoad();

    //    MapPrefabs::getInstance().LoadConfig("config");
    //
    //    auto prefab = MapPrefabs::getInstance().getPrefab("prefab3");
    //    auto prefab2 = MapPrefabs::getInstance().getPrefab("prefab2");
    //    auto prefab3 = MapPrefabs::getInstance().getPrefab("prefab4");
    //
    //    std::vector<MapPrefab> mapElements = {prefab, prefab2, prefab3};
    //
    //    prefab.centerToConnectorPosition(0);
    //    prefab2.centerToConnectorPosition(0);
    //    prefab3.centerToConnectorPosition(0);
    //
    //
    //
    //    auto rooms = 0;
    //    auto attempts = 0;
    //    auto currentPrefabIndex =
    //        Rng::getInstance().getRandomInt(0, mapElements.size() - 1);
    //    auto currentPrefab = mapElements[currentPrefabIndex];
    //    currentPrefab.setTranslation(100, 100);
    //
    //    hero_.set(currentPrefab.baricenter().col,
    //    currentPrefab.baricenter().row); std::shared_ptr<Room> currentRoom =
    //        Room::createFromMapElement(currentPrefab);
    //
    ////    Graph<Room> graph{currentRoom};
    //
    //    auto r = Room::createFromMapElement(currentPrefab);
    //    heroRoom = r;
    //    map_->addRoom(r);
    //    auto map_ = GameCtx::getInstance().map();

    //    raylib::Camera2D camera{};
    //
    //    camera.offset = (Vector2){25*renderer_->getTileSize().x,
    //    10*renderer_->getTileSize().y}; camera.target.x =
    //    hero_.x()*renderer_->getTileSize().x; camera.target.y =
    //    hero_.y()*renderer_->getTileSize().y; camera.rotation = 0.0f;
    //    camera.zoom = 1.0f;

    //    auto otherPrefabIndex = 0;
    //    MapPrefab otherPrefab;

    //    int currentConnector = 0;
    while (!Renderer::getInstance().shouldEnd()) {
        //        auto scene = SceneManager::getInstance().getCurrentScene();
        SceneManager::getInstance().getCurrentScene()->handleInput();
        SceneManager::getInstance().getCurrentScene()->update();

        // TODO: do this in a better way!no no, do this!
        //        drawUiInfo.inventory.clear();
        //        auto inventory = hero_.getInventory();
        //        std::transform(
        //            std::begin(inventory), std::end(inventory),
        //            std::back_inserter(drawUiInfo.inventory),
        //            [](const auto& item) { return item->name(); });
        //        // process input
        //        if (waitUserInput_) {
        //            cmd = state_->handleInput();
        //
        //            if (cmd != nullptr) {
        //
        //                waitUserInput_ = false;
        //            }
        //        }

        // update
        //        if (!waitUserInput_) {
        //            drawUiInfo.messages.clear();
        //            cmd->execute(&hero_, *map_);
        //            camera.target.x = hero_.x()*renderer_->getTileSize().x;
        //            camera.target.y = hero_.y()*renderer_->getTileSize().y;
        //
        //            heroRoom = map_->queryRoom(hero_.x(), hero_.y());
        //            delete cmd;
        ////            prefab.setTranslation(100, 100);
        //            // prefab2.setTranslation(40,40);
        //
        //            map_->updateUiInfo(hero_.x(), hero_.y(), drawUiInfo);
        //            waitUserInput_ = true;
        //        }

        //        if (IsKeyPressed(KEY_F)) {
        //            while (attempts < 10) {
        //
        //                if (attempts == 0) {
        //                    otherPrefabIndex =
        //                    Rng::getInstance().getRandomInt(
        //                        0, mapElements.size() - 1);
        //
        //                    otherPrefab = mapElements[otherPrefabIndex];
        //                }
        //                auto roomIdx = Rng::getInstance().getRandomInt(
        //                    0, map_->roomWithConnectionCount() - 1);
        //                auto added = map_->addPrefabTo(roomIdx, otherPrefab);
        //                if (added) {
        //                    fmt::print("Added prefab to room {}\n", roomIdx);
        //                    fmt::print("rooms = {}\n", map_->roomCount());
        //                    attempts = 0;
        //                    break;
        //                } else {
        //                    fmt::print(".");
        //                    attempts++;
        //                }
        //            }
        //        }

        //        if (IsKeyPressed(KEY_W)) {
        //            camera.target.y = camera.target.y - 50;
        //        }
        //        if (IsKeyPressed(KEY_S)) {
        //            camera.target.y = camera.target.y + 50;
        //        }
        //        if (IsKeyPressed(KEY_A)) {
        //            camera.target.x = camera.target.x - 50;
        //        }
        //        if (IsKeyPressed(KEY_D)) {
        //            camera.target.x = camera.target.x + 50;
        //        }

        //        if (IsKeyPressed(KEY_I)) {
        //            fmt::print("ITEMS: ");
        //            for(auto& item: drawUiInfo.inventory) {
        //                fmt::print("{}\t", item);
        //            }
        //            fmt::print("\n-------------\n");
        //        }

        // Camera zoom controls
        //        camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
        //
        //        if (camera.zoom > 3.0f)
        //            camera.zoom = 3.0f;
        //        else if (camera.zoom < 0.1f)
        //            camera.zoom = 0.1f;

        // draw
        SceneManager::getInstance().getCurrentScene()->render();
        //        renderer_->prepare();
        //
        //        BeginMode2D(camera);
        //
        //        map_->draw(heroRoom);
        //        renderer_->drawEntity({hero_.x(), hero_.y(), "@"});
        ////        renderer_->drawRays(heroRoom, hero_);
        //        EndMode2D();
        //        renderer_->drawUi(drawUiInfo);
        //        renderer_->draw();
    }
}

void Game::setup(const GameOptions& options) {
    renderer_->setup();

    //   map_ = new Map(options.width, options.height);
}

bool Game::processInput() {
    if (IsKeyPressed(KEY_LEFT)) {
        fmt::print("Left pressed\n");
        hero_.moveLeft();

        return true;
    }

    if (IsKeyPressed(KEY_RIGHT)) {
        fmt::print("Right pressed\n");
        hero_.moveRight();
        return true;
    }

    if (IsKeyPressed(KEY_UP)) {
        fmt::print("Up pressed\n");
        hero_.moveUp();
        return true;
    }

    if (IsKeyPressed(KEY_DOWN)) {
        fmt::print("Down pressed\n");
        hero_.moveDown();
        return true;
    }

    return false;
}

void Game::update() { fmt::print("Game updated\n"); }

Game::~Game() {}
