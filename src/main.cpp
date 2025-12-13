#include <iostream>
#include "../include/raylib-cpp.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

int screenWidth = 800;
int screenHeight = 450;

raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

int main() {


    SetTargetFPS(60);

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    #else

    while (!window.ShouldClose())
    {
        BeginDrawing();

        window.ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        // Object methods.

        EndDrawing();
    }

    #endif

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}

void UpdateDrawFrame() {
    BeginDrawing();

    window.ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    // Object methods.

    EndDrawing();
}