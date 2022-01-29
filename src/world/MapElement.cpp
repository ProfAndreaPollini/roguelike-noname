//
// Created by pollini on 14/01/2022.
//

#include "fmt/core.h"

#include "MapElement.h"

Direction rotateDirection(Direction dir, int n) {
    fmt::print("rotateDirection: {} {}\n", static_cast<int>(dir), (static_cast<int>(dir) + n) % 4);
    return static_cast<Direction>((static_cast<int>(dir) + n) % 4);
}

bool isDirectionFacing(Direction dir1, Direction dir2) {
    fmt::print("isDirectionFacing: {} {}\n", static_cast<int>(dir1), static_cast<int>(dir2));
    return (static_cast<int>(dir1) + 2) % 4 == static_cast<int>(dir2);
}
