#include <iostream>

#include "../include/raylib-cpp.hpp"
#include "class/Game.hpp"
#include "class/Sequencer.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame();

int screenWidth = 950;
int screenHeight = 950;

raylib::Window window(screenWidth, screenHeight, "Project: Neutronic Decay");

Game game;

void init() {
    game.init();
}

int main() {

    init();
    SetTargetFPS(1200);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    #else
    while (!window.ShouldClose()) {
        UpdateDrawFrame();
    }
    #endif

    return 0;
}

void UpdateDrawFrame() {
    //  -   -   -  // - - - - - UPDATE PART - - - - - //

    game.update(GetFrameTime());

    BeginDrawing(); // - - - - - DRAW PART - - - - - //

    window.ClearBackground(LIGHTGRAY);

    game.draw();

    DrawFPS(10, 10);

    EndDrawing();
}
