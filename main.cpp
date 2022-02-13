
#include "Game.h"
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
//#define RAYGUI_STATIC    // Only if you want to keep raygui functionality
// internal to current module
#define BUILD_WITH_EASY_PROFILER
#include <easy/profiler.h>

#include "extras/raygui.h"

int main() {
    EASY_MAIN_THREAD;
    // std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
    profiler::startListen();
    Game game{};
    game.setup();
    game.run();
    return 0;
}
