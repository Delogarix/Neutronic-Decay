#include <iostream>

#include "../include/raylib-cpp.hpp"
#include "class/Game.hpp"
#include "class/Sequencer.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame();

int screenWidth = 850;
int screenHeight = 850;
float deltaTime = 0.0f;

raylib::Window window(screenWidth, screenHeight, "Project: Neutronic Decay");

Game game;

void init() {
    game.init();
}

int main() {

    init();
    SetTargetFPS(1200);

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
    raylib::Color inner = raylib::Color(170, 170, 170);
    raylib::Color outer = raylib::Color(100, 100, 100);

    game.update(deltaTime);
    deltaTime = GetFrameTime();
    if (deltaTime > 0.5f) deltaTime = 0.5f;

    BeginDrawing(); // - - - - - DRAW PART - - - - - //

    DrawCircleGradient(GetScreenWidth()/2 ,GetScreenHeight()/2, 550, inner, outer);
    game.draw();

    DrawFPS(10, 10);

    EndDrawing();
}
