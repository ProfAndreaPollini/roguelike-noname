//
// Created by pollini on 11/01/2022.
//

#include  "raylib-cpp.hpp"

#include "PlayerTurn.h"

#include "MoveCommand.h"

Command * PlayerTurn::handleInput() {
    if(IsKeyPressed(KEY_LEFT)){
        return new MoveCommand(-1,0);
    }
    if(IsKeyPressed(KEY_RIGHT)){
        return new MoveCommand(1,0);
    }
    if(IsKeyPressed(KEY_UP)){
        return new MoveCommand(0,-1);
    }
    if(IsKeyPressed(KEY_DOWN)){
        return new MoveCommand(0,1);
    }
    return nullptr;
}
