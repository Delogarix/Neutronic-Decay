#include <iostream>

#include "../include/raylib-cpp.hpp"
#include "class/Game.hpp"
#include "class/Sequencer.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame();

int screenWidth = 750;
int screenHeight = 750;
float deltaTime = 0.0f;

raylib::Window window(screenWidth, screenHeight, "Project: Neutronic Decay");

Game game;

void init() {
    game.init();
}

int main() {

    init();
    SetTargetFPS(75);

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


    game.update(deltaTime);
    deltaTime = GetFrameTime();
    if (deltaTime > 0.5f) deltaTime = 0.5f; // Hard choice but best option for now

    BeginDrawing(); // - - - - - DRAW PART - - - - - //

    window.ClearBackground(LIGHTGRAY);

    game.draw();

    DrawFPS(10, 10);

    EndDrawing();
}
