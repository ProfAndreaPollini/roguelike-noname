
#include "Game.h"

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
//#define RAYGUI_STATIC    // Only if you want to keep raygui functionality internal to current module
#include "extras/raygui.h"

int main() {
    //std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();

    Game game{};
    game.setup();
    game.run();
    return 0;
}
