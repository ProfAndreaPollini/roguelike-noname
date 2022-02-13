//
// Created by pollini on 10/01/2022.
//

#include "Renderer.h"

#include <easy/profiler.h>

#include <ranges>

#include "GameCtx.h"
#include "MapAlgorithms.h"
#include "Services.h"
#include "components/Inventory.h"
#include "components/MapPosition.h"
#include "components/Position.h"
#include "components/Tags.h"

void Renderer::prepare() const {
    BeginDrawing();
    window_->ClearBackground(BLACK);
}

void Renderer::draw() const {
    //    DrawText("@", 190, 200, 20, RED);
    //    EndMode2D();
    EndDrawing();
}

void Renderer::setup() {
    auto ptr = std::make_unique<raylib::Window>(options.width, options.height, options.title);
    window_.swap(ptr);

    font_ = LoadFont("assets/fonts/roguelike-fonts-1.0/whitrabt.ttf");
    fontSize_ = MeasureTextEx(font_, "A", 20, 0);
    fontSize_.x = (int)fontSize_.x;
    fontSize_.y = (int)fontSize_.y;
}

void Renderer::drawRoom(const Room::RoomPtr& room, entt::entity heroRoomEntity, std::set<entt::entity> neighbours,
                        const Viewport& viewport) const {
    //        prefab.setDirection(Direction::EAST);
    EASY_FUNCTION(profiler::colors::Magenta);
    EASY_BLOCK("get variables");
    auto& ecs = Services::Ecs::ref();

    auto& map = ecs.registry.ctx().at<Map>();
    const auto& roomsBFS = map.roomConnectionsBFS();
    const auto& lastRoom = roomsBFS.back();
    auto cellView = ecs.registry.view<Position, CellTag, RenderInfo>();
    const auto& doors = map.doors();
    EASY_END_BLOCK;
    //      auto baricenter = room.baricenter();
    EASY_BLOCK("cell loop");

    auto cells_ = room->cells();

    for (const auto cellEntity : room->cells()) {
        EASY_BLOCK("test if it is a door");
        if (doors.contains(cellEntity)) {
            continue;
        }
        EASY_END_BLOCK;
        EASY_BLOCK("entt get");

        const auto& [position, cell, renderInfo] = cellView.get(cellEntity);

        if (!viewport.contains(position.col, position.row)) continue;
        //        auto isCurrent = room == heroRoom;
        auto inNeighbourRoom = neighbours.contains(cell.room);
        auto isVisited = room->visited();
        if (!isVisited && !inNeighbourRoom) continue;

        auto drawCol = position.col;
        auto drawRow = position.row;

        if (position.row < 0 || position.col < 0) continue;

        if (isVisited) {
            drawRectangle(drawCol, drawRow, renderInfo.bgColor);
            drawText(TextFormat("%c", renderInfo.glyph), drawCol, drawRow, renderInfo.textColor);
        } else if (inNeighbourRoom) {
            drawRectangle(drawCol, drawRow, renderInfo.bgColor);
            drawRectangle(position.col, position.row, {50, 50, 50, 50});
        }
    }
    EASY_END_BLOCK;
    EASY_BLOCK("door loop");
    for (auto door : doors) {
        const auto& position = ecs.registry.get<Position>(door);
        const auto& info = ecs.registry.get<DoorTag>(door);
        auto drawCol = position.col;
        auto drawRow = position.row;
        drawText(info.glyph, drawCol, drawRow, YELLOW);
    }
    EASY_END_BLOCK;
}
void Renderer::drawAstar(AStar& astar) const {
    for (auto& cell : astar.positions()) {
        drawRectangle(cell.col, cell.row, RED);
    }
    for (auto& cell : astar.getPath()) {
        drawRectangle(cell.col, cell.row, BLUE);
    }
}
Renderer::Renderer(const RenderOptions& options) : options(options) {
    //    auto& ecs = Services::Ecs::ref();
    //    cellsView = ecs.registry.view<Position, CellTag, Inventory>();
}

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines
// intersect the intersection point may be stored in the floats i_x and i_y.
auto getLineIntersection(float p0X, float p0Y, float p1X, float p1Y, float p2X, float p2Y, float p3X, float p3Y,
                         float& iX, float& iY) -> bool {
    auto s1X = p1X - p0X;
    auto s1Y = p1Y - p0Y;
    auto s2X = p3X - p2X;
    auto s2Y = p3Y - p2Y;

    auto s = (-s1Y * (p0X - p2X) + s1X * (p0Y - p2Y)) / (-s2X * s1Y + s1X * s2Y);
    auto t = (s2X * (p0Y - p2Y) - s2Y * (p0X - p2X)) / (-s2X * s1Y + s1X * s2Y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        // Collision detected
        iX = p0X + (t * s1X);
        iY = p0Y + (t * s1Y);
        return true;
    }

    return false;  // No collision
}

std::vector<MapPosition> Bresenham(int x1, int y1, int const x2, int const y2) {
    std::vector<MapPosition> ret;
    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix(int(delta_x > 0) - int(delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;

    //    plot(x1, y1);
    ret.push_back(MapPosition::fromRowCol(y1, x1));

    if (delta_x >= delta_y) {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));

        while (x1 != x2) {
            // reduce error, while taking into account the corner case of error
            // == 0
            if ((error > 0) || (!error && (ix > 0))) {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            x1 += ix;

            ret.push_back(MapPosition::fromRowCol(y1, x1));
        }
    } else {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (y1 != y2) {
            // reduce error, while taking into account the corner case of error
            // == 0
            if ((error > 0) || (!error && (iy > 0))) {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing

            error += delta_x;
            y1 += iy;

            ret.push_back(MapPosition::fromRowCol(y1, x1));
        }
    }
    return ret;
}

void DDAWallIntersection(float posX, float posY, float endX, float endY, int cellCol, int cellRow, float angle,
                         float& dist) {
    double cameraX = 2 * (angle - 45) / (double)90.0 - 1;  // x-coordinate in camera space

    float mapX = posX;
    float mapY = posY;

    float dirX = 0;
    float dirY = -1;
    float planeX = 1.0;
    float planeY = 0.0;

    double rayDirX = dirX + planeX * cameraX;
    double rayDirY = dirY + planeY * cameraX;

    // length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

    double perpWallDist;

    // what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;

    bool hit = false;  // was there a wall hit?
    int side;          // was a NS or a EW wall hit?

    // calculate step and initial sideDist
    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    // perform DDA
    while (hit == false) {
        // jump to next map square, either in x-direction, or in y-direction
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY -= deltaDistY;
            mapY += stepY;
            side = 1;
        }
        // Check if ray has hit a wall
        if (mapX == cellCol && mapY == cellRow) {
            hit = true;
        }
        fmt::print("{} {} {} {} {} {}\n", mapX, mapY, cellCol, cellRow, sideDistX, sideDistY);
    }

    if (side == 0)
        perpWallDist = (sideDistX - deltaDistX);
    else
        perpWallDist = (sideDistY - deltaDistY);

    dist = perpWallDist;
}
