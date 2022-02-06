//
// Created by pollini on 10/01/2022.
//

#ifndef RL_DA_ZERO_RENDERER_H
#define RL_DA_ZERO_RENDERER_H

#include <algorithm>
#include <cmath>
#include <memory>

//#include "GameCtx.h"

#include "Hero.h"
#include "MapAlgorithms.h"
#include "MapElement.h"
#include "MapPrefab.h"
#include "Room.h"
#include "components/Inventory.h"
#include "components/MapPosition.h"
#include "components/Position.h"
#include "components/Tags.h"
#include "entt/entity/runtime_view.hpp"
#include "extras/raygui.h"
#include "raylib-cpp.hpp"

std::vector<MapPosition> Bresenham(int x1, int y1, int const x2, int const y2);

const double pi = std::acos(-1);

// const raylib::Color WALL_COLOR = LIGHTGRAY;

struct RenderOptions {
    int width;
    int height;
    const char* title;

    RenderOptions() : width(1920), height(1080), title("RL-DA-Zero") {}
};

struct DrawEntityInfo {
    int x;
    int y;
    const char* c;

    DrawEntityInfo() : x(0), y(0), c(".") {}

    [[maybe_unused]] DrawEntityInfo(int x, int y, const char* c) : x(x), y(y), c(c) {}
};

struct DrawCellInfo {
    int x;
    int y;
    const char* feature;
    const char* item;

    DrawCellInfo() : x(0), y(0), feature(""), item() {}

    [[maybe_unused]] DrawCellInfo(int x, int y, const char* feature, const char* item)
        : x(x), y(y), feature(feature), item(item) {}
};

struct DrawUIInfo {
    std::vector<std::string> messages;
    std::vector<std::string> inventory;
};

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines
// intersect the intersection point may be stored in the floats i_x and i_y.
auto getLineIntersection(float p0X, float p0Y, float p1X, float p1Y, float p2X, float p2Y, float p3X, float p3Y,
                         float& iX, float& iY) -> bool;

void DDAWallIntersection(float startX, float startY, float endX, float endY, int cellCol, int cellRow, float angle,
                         float& ix);

class Renderer {
    Renderer(const RenderOptions& options = RenderOptions());

   public:
    static Renderer& getInstance() {
        static Renderer instance;
        return instance;
    }

    ~Renderer() { UnloadFont(font_); }

    void setup();
    void prepare() const;
    void draw() const;

    [[maybe_unused]] void drawEntity(DrawEntityInfo drawInfo) { drawText(drawInfo.c, drawInfo.x, drawInfo.y, RED); }

    void drawText(const char* text, float x, float y, raylib::Color color) const {
        raylib::Vector2 position = {x, y};
        drawText(text, position, BLUE);
    }

    void drawText(const char* text, raylib::Vector2 position, raylib::Color color) const {
        position.x *= fontSize_.x;
        position.y *= fontSize_.y;
        raylib::DrawTextEx(font_, text, position, 14, (float)0, BLUE);
    }
    void drawRectangle(raylib::Vector2 p, float w, float h, raylib::Color c) const { drawRectangle(p.x, p.y, w, h, c); }

    void drawRectangle(raylib::Vector2 p, raylib::Color c) const {
        drawRectangle(p.x, p.y, fontSize_.x, fontSize_.y, c);
    }

    void drawRectangle(float x, float y, raylib::Color c) const {
        DrawRectangle(x * fontSize_.x, y * fontSize_.y, fontSize_.x, fontSize_.y, c);
    }

    void drawRectangle(float x, float y, float w, float h, raylib::Color c) const {
        DrawRectangle(x * fontSize_.x, y * fontSize_.y, w, h, c);
    }

    void drawCircle(float x, float y, float r, raylib::Color c) const {
        DrawCircle(x * fontSize_.x, y * fontSize_.y, r, c);
    }

    void drawAstar(AStar& astar) const;

    void drawRoom(Room::RoomPtr room, Room::RoomPtr heroRoom, std::vector<Room::RoomPtr> neighbours, int col,
                  int row) const;

    [[maybe_unused]] void drawUi(const DrawUIInfo& uiInfo) {
        int y = 10;
        int x = 100;

        int iy = 4;
        int ix = 4;

        for (const auto& item : uiInfo.inventory) {
            drawText(item.c_str(), ix, iy, WHITE);
            DrawRectangle(ix, iy, 30, 30, WHITE);
            iy++;
        }

        for (const auto& message : uiInfo.messages) {
            drawText(message.c_str(), x, y, BLACK);
            x += 20;
        }
    }

    bool shouldEnd() const { return window_->ShouldClose(); }

    const raylib::Vector2 getTileSize() const { return fontSize_; }

   private:
    RenderOptions options;
    std::unique_ptr<raylib::Window> window_;
    raylib::Font font_;
    raylib::Vector2 fontSize_;
    //    entt::view<Position, CellTag, Inventory> cellsView;
};

#endif  // RL_DA_ZERO_RENDERER_H
