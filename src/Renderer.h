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
#include "MapPosition.h"
#include "MapPrefab.h"
#include "Room.h"
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

    [[maybe_unused]] DrawEntityInfo(int x, int y, const char* c)
        : x(x), y(y), c(c) {}
};

struct DrawCellInfo {
    int x;
    int y;
    const char* feature;
    const char* item;

    DrawCellInfo() : x(0), y(0), feature(""), item() {}

    [[maybe_unused]] DrawCellInfo(int x, int y, const char* feature,
                                  const char* item)
        : x(x), y(y), feature(feature), item(item) {}
};

struct DrawUIInfo {
    std::vector<std::string> messages;
    std::vector<std::string> inventory;
};

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines
// intersect the intersection point may be stored in the floats i_x and i_y.
auto getLineIntersection(float p0X, float p0Y, float p1X, float p1Y, float p2X,
                         float p2Y, float p3X, float p3Y, float& iX, float& iY)
    -> bool;

void DDAWallIntersection(float startX, float startY, float endX, float endY,
                         int cellCol, int cellRow, float angle, float& ix);

class Renderer {
    Renderer(const RenderOptions& options = RenderOptions())
        : options(options) {}

   public:
    static Renderer& getInstance() {
        static Renderer instance;
        return instance;
    }

    ~Renderer() { UnloadFont(font_); }

    void setup();
    void prepare() const;
    void draw() const;

    [[maybe_unused]] void drawEntity(DrawEntityInfo drawInfo) {
        drawText(drawInfo.c, drawInfo.x, drawInfo.y, RED);
    }

    void drawText(const char* text, float x, float y,
                  raylib::Color color) const {
        raylib::Vector2 position = {x, y};
        drawText(text, position, BLUE);
    }

    void drawText(const char* text, raylib::Vector2 position,
                  raylib::Color color) const {
        position.x *= fontSize_.x;
        position.y *= fontSize_.y;
        raylib::DrawTextEx(font_, text, position, 14, (float)0, BLUE);
    }
    void drawRectangle(raylib::Vector2 p, float w, float h,
                       raylib::Color c) const {
        drawRectangle(p.x, p.y, w, h, c);
    }

    void drawRectangle(raylib::Vector2 p, raylib::Color c) const {
        drawRectangle(p.x, p.y, fontSize_.x, fontSize_.y, c);
    }

    void drawRectangle(float x, float y, raylib::Color c) const {
        DrawRectangle(x * fontSize_.x, y * fontSize_.y, fontSize_.x,
                      fontSize_.y, c);
    }

    void drawRectangle(float x, float y, float w, float h,
                       raylib::Color c) const {
        DrawRectangle(x * fontSize_.x, y * fontSize_.y, w, h, c);
    }

    void drawCircle(float x, float y, float r, raylib::Color c) const {
        DrawCircle(x * fontSize_.x, y * fontSize_.y, r, c);
    }

    [[maybe_unused]] void drawRays(Room::RoomPtr room, const Hero& hero) {
        // x =x0+t*x_d
        // y =y0+t*y_d
        float startX = hero.x();
        float startY = hero.y();
        float endX = hero.x();
        float endY = hero.y();
        double angle = pi / 4;
        auto cells = room->cells();
        std::vector<RoomElement> walls;
        std::copy_if(cells.begin(), cells.end(), std::back_inserter(walls),
                     [](const RoomElement& cell) {
                         return cell.cell.type == CellType::CELL_WALL;
                     });

        //            fmt::print("?>>> {} {}\t",std::fabs(endX - startX) ,
        //            std::fabs(endY - startY));
        //            fmt::print("--------------------\n");
        for (angle = 45; angle < 135; angle += 1) {
            for (int i = 0; i < walls.size(); ++i) {
                auto cell = walls[i];
                float dist = 0;

                endY = startY - std::sinf(angle * (pi / 180.0)) * 10;
                endX = startX + std::cosf(angle * (pi / 180.0)) * 10;
                //                while (std::fabs(endX - startX) +
                //                std::fabs(endY - startY) <
                //                       20) {
                auto path = Bresenham(startX, startY, endX, endY);

                for (auto& p : path) {
                    //                        fmt::print("{} {}\t", p.col,
                    //                        p.row); fmt::print("{} {}\n",
                    //                        cell.coords().col,
                    //                                   cell.coords().row);
                    if (p == cell.coords()) {
                        drawCircle(p.col, p.row, 10, GREEN);
                        //                        DDAWallIntersection(startX,
                        //                        startY, endX, endY,
                        //                                            cell.coords().col,
                        //                                            cell.coords().row,
                        //                                            angle,dist);
                        //                        fmt::print("{} {}\t", dist,
                        //                        angle);
                    } else
                        drawRectangle(p.col, p.row, RED);
                }
            }
        }
    }
    //        float xEnd =0;
    //        float yEnd =0;
    //        auto isIntersecting =
    //        getLineIntersection(hero.x(),hero.y(),hero.x(),hero.y()-50,room->x,room->y,room->x+room->width,room->y,xEnd,yEnd);
    //        DrawLine(drawInfo.x*14, drawInfo.y*20, drawInfo.x*14, 0, RED);

    //    [[maybe_unused]] static void drawCell(const DrawCellInfo& drawInfo) {
    //        DrawText(drawInfo.feature, drawInfo.x * 14, drawInfo.y * 20, 20,
    //        RED); DrawText(drawInfo.item, drawInfo.x * 14, drawInfo.y * 20,
    //        20, GREEN);
    //    }

    //    [[maybe_unused]] static void drawConnection(const DrawCellInfo&
    //    drawInfo) {
    //        DrawText(drawInfo.feature, drawInfo.x * 14, drawInfo.y * 20, 20,
    //        BLUE); DrawText(drawInfo.item, drawInfo.x * 14, drawInfo.y * 20,
    //        20, BLUE);
    //    }

    //    static void drawRoom( Room& room) {
    //        for (auto& cell : room.cells()) {
    //            auto elementCell = cell.position;
    //            DrawText("#", std::abs( elementCell.coords.col) * 14,
    //            std::abs(elementCell.coords.row) * 20, 20, BLUE);
    //        }
    //    }
    //    void drawPrefab(MapPrefab& prefab, int col, int row) {
    //        //        prefab.setDirection(Direction::EAST);
    //
    //        auto baricenter = prefab.baricenter();
    //        for (auto& cell : prefab.cells()) {
    //            //            auto x = col + cell.col - baricenter.col;
    //            //            auto y = row + cell.row - baricenter.row;
    //            //            fmt::print("{} {}\n", x, y);
    //            if (cell.coords.row > 0 && cell.coords.col > 0) {
    //                DrawText("#", std::abs(col + cell.coords.col) * 14,
    //                         std::abs(row + cell.coords.row) * 20, 20, BLUE);
    //            }
    //        }
    //
    //        for (const auto& connector : prefab.connectors()) {
    //            auto coords = connector.position();
    //            auto direction = connector.direction();
    //            if (coords.row > 0 && coords.col > 0) {
    //                raylib::Color c;
    //                switch (direction) {
    //                    case Direction::NORTH:
    //                        c = PURPLE;
    //                        DrawRectangle(coords.col * 14, coords.row * 20 -
    //                        10, 14,
    //                                      20, c);
    //                        break;
    //                    case Direction::SOUTH:
    //                        c = BLUE;
    //                        DrawRectangle(coords.col * 14, coords.row * 20 +
    //                        10, 14,
    //                                      20, c);
    //                        break;
    //                    case Direction::EAST:
    //                        c = RED;
    //                        DrawRectangle(coords.col * 14 + 10, coords.row *
    //                        20, 14,
    //                                      20, c);
    //                        break;
    //                    case Direction::WEST:
    //                        c = GREEN;
    //                        DrawRectangle(coords.col * 14 - 10, coords.row *
    //                        20, 14,
    //                                      20, c);
    //                        break;
    //                    default:
    //                        c = BLACK;
    //                        break;
    //                }
    //
    //                DrawRectangle(col * 14 + coords.col * 14,
    //                              row * 20 + coords.row * 20, 14, 20, c);
    //                drawText(">", (col + coords.col), (row + coords.row),
    //                BLACK);
    //            }
    //        }
    //
    //        auto selectedCoords = prefab.selectedConnectorCoords();
    //        if (selectedCoords.row > 0 && selectedCoords.col > 0) {
    //            DrawRectangle(col * 14 + selectedCoords.col * 14,
    //                          row * 20 + selectedCoords.row * 20, 14, 20,
    //                          YELLOW);
    //        }
    //    }

    void drawAstar(AStar& astar) const;

    void drawRoom(Room::RoomPtr room, Room::RoomPtr heroRoom, int col,
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
};

#endif  // RL_DA_ZERO_RENDERER_H
