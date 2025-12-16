#include <iostream>
#include "../include/raylib-cpp.hpp"
#include "class/AnimatedSprite.hpp"
#include "class/Entity.hpp"
#include "class/Player.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame();

int screenWidth = 1500;
int screenHeight = 800;

raylib::Window window(screenWidth, screenHeight, "Project: Neutronic Decay");
raylib::Texture2D iridiumTex = LoadTexture("assets/iridium-core.png");
raylib::Texture2D redArrowTex = LoadTexture("assets/red-arrow.png");
AnimatedSprite iridium = AnimatedSprite(&iridiumTex, 5, 0, 3.6f, 5, 1);
AnimatedSprite redArrow = AnimatedSprite(&redArrowTex, 8, 0, 9.5f, 5, 1);

Player player(redArrow);

void init() {
    player.position = raylib::Vector2(GetScreenWidth()/2, GetScreenHeight()/2);
}

int main() {


    SetTargetFPS(60);

    init();

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