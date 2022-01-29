//
// Created by pollini on 27/01/2022.
//

#include "PlayScene.h"

#include "GameCtx.h"
#include "MapPrefabs.h"
#include "MoveCommand.h"
#include "UIDebugOverlay.h"
#include "LogOverlay.h"

void PlayScene::handleInput() {
    auto map = GameCtx::getInstance().map();

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

void PlayScene::handleRoomCreate(Rc<Map> map) const {
    int attempts = 0;
    auto otherPrefabIndex = 0;
    MapPrefab otherPrefab;

    std::vector<MapPrefab> mapElements = MapPrefabs::getInstance().getPrefabs();

    while (attempts < 10) {
        if (attempts == 0) {
            otherPrefabIndex =
                Rng::getInstance().getRandomInt(0, mapElements.size() - 1);

            otherPrefab = mapElements[otherPrefabIndex];
        }
        auto roomIdx = Rng::getInstance().getRandomInt(
            0, map->roomWithConnectionCount() - 1);
        auto added = map->addPrefabTo(roomIdx, otherPrefab);
        if (added) {
            fmt::print("Added prefab to room {}\n", roomIdx);
            fmt::print("rooms = {}\n", map->roomCount());
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
        auto hero = GameCtx::getInstance().hero();
        auto map = GameCtx::getInstance().map();
        //        drawUiInfo.messages.clear();
        cmd_->execute(hero.get(), *map);
        camera_.target.x = hero->x() * Renderer::getInstance().getTileSize().x;
        camera_.target.y = hero->y() * Renderer::getInstance().getTileSize().y;

        heroRoom_ = map->queryRoom(hero->x(), hero->y());
        delete cmd_;
        //            prefab.setTranslation(100, 100);
        // prefab2.setTranslation(40,40);

        //        map->updateUiInfo(hero->x(), hero->y(), drawUiInfo);
        waitUserInput_ = true;
    }
}

void PlayScene::render() {
    Renderer::getInstance().prepare();

    auto hero = GameCtx::getInstance().hero();
    auto map = GameCtx::getInstance().map();

    BeginMode2D(camera_);

    map->draw(heroRoom_);
    Renderer::getInstance().drawEntity({hero->x(), hero->y(), "@"});
    //        renderer_->drawRays(heroRoom, hero_);
    EndMode2D();
    //    Renderer::getInstance().drawUi(drawUiInfo);
    for (const auto& overlay : overlays_) {
        overlay->draw();
    }
    Renderer::getInstance().draw();
}

PlayScene::PlayScene() : waitUserInput_(true) {
    //    raylib::Camera2D camera{};
    auto debugUi = new UIDebugOverlay();
    overlays_.push_back(std::shared_ptr<UIDebugOverlay>(debugUi));

    auto logUi = new LogOverlay({400,10 }, {400,400});
    overlays_.push_back(std::shared_ptr<LogOverlay>(logUi));
}
void PlayScene::onLoad() {
    generateMap();
    auto hero = GameCtx::getInstance().hero();

    camera_.offset = (Vector2){25 * Renderer::getInstance().getTileSize().x,
                               10 * Renderer::getInstance().getTileSize().y};
    camera_.target.x = hero->x() * Renderer::getInstance().getTileSize().x;
    camera_.target.y = hero->y() * Renderer::getInstance().getTileSize().y;
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

    auto hero = GameCtx::getInstance().hero();
    auto map = GameCtx::getInstance().map();

    auto rooms = 0;
    auto attempts = 0;
    auto currentPrefabIndex =
        Rng::getInstance().getRandomInt(0, mapElements.size() - 1);
    auto currentPrefab = mapElements[currentPrefabIndex];
    currentPrefab.setTranslation(100, 100);

    hero->set(currentPrefab.baricenter().col, currentPrefab.baricenter().row);
    std::shared_ptr<Room> currentRoom =
        Room::createFromMapElement(currentPrefab);

    //    Graph<Room> graph{currentRoom};

    auto r = Room::createFromMapElement(currentPrefab);
    heroRoom_ = r;
    map->addRoom(r);
}
Command* PlayScene::handleUserInput() {
    if (IsKeyPressed(KEY_LEFT)) {
        return new MoveCommand(-1, 0);
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        return new MoveCommand(1, 0);
    }
    if (IsKeyPressed(KEY_UP)) {
        return new MoveCommand(0, -1);
    }
    if (IsKeyPressed(KEY_DOWN)) {
        return new MoveCommand(0, 1);
    }
    return nullptr;
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
