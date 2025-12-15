#include <iostream>
#include "../include/raylib-cpp.hpp"
#include "class/AnimatedSprite.hpp"
#include "class/Entity.hpp"
#include "class/Player.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// WEB Cmd
/*
 * em++ -o game.html main.cpp -Os -Wall ../lib/Web/libraylib.a -I. -I ../include -L. -s USE_GLFW=3
--shell-file ../shell/shell.html -DPLATFORM_WEB --preload-file assets
 */

void UpdateDrawFrame();

int screenWidth = 800;
int screenHeight = 450;

raylib::Window window(screenWidth, screenHeight, "Project: Neutronic Decay");
raylib::Texture2D iridiumTex = LoadTexture("assets/iridium-core.png");
AnimatedSprite iridium = AnimatedSprite(&iridiumTex, 5, 0, 3.6f, 5, 1);

Player player(iridium);

int main() {


    SetTargetFPS(60);

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    #else

    while (!window.ShouldClose())
    {
        UpdateDrawFrame();
    }

    #endif

    return 0;
}

void UpdateDrawFrame() {

    player.update(GetFrameTime());

    BeginDrawing();

    window.ClearBackground(RAYWHITE);

    DrawText("Welcome to neutronic-decay !", 220, 200, 20, DARKGREEN);
    player.draw();


    EndDrawing();
}