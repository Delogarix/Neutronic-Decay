#include <iostream>
#include <array>
#include "../include/raylib-cpp.hpp"
#include "class/AnimatedSprite.hpp"
#include "class/Entity.hpp"
#include "class/Player.hpp"
#include "class/Arrow.hpp"
#include "class/Game.hpp"
#include "class/Homing.hpp"
#include "class/Sequencer.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

raylib::Vector2 getRandomVector() {
    raylib::Vector2 vec = UP;
    float angle = GetRandomValue(0, 360);
    vec = vec.Rotate(angle * DEG2RAD);
    return vec;
}

void UpdateDrawFrame();

int screenWidth = 1300;
int screenHeight = 900;

float sliderX, sliderSpeed;

raylib::Window window(screenWidth, screenHeight, "Project: Neutronic Decay");

Game game;

void drawActionBar();
void drawSlider();

raylib::Texture2D boulderTex = LoadTexture("assets/aqua-sphere.png");
AnimatedSprite boulderS = AnimatedSprite(&boulderTex, 6, 0, 10.0f, 7, 1);


void init() {
    sliderX = 400;
    sliderSpeed = 1;
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

    window.ClearBackground(RAYWHITE);

    game.draw();

    drawActionBar();
    drawSlider();

    DrawFPS(30, 30);

    EndDrawing();
}


void drawActionBar() {
    int length = 800;
    DrawRectangleGradientH(GetScreenWidth()/2 - length/2, GetScreenHeight() - 60,length, 50 , RED, BLUE);
}

void drawSlider() {

    DrawRectangle(sliderX, GetScreenHeight() - 55, 10, 20, BLACK);
    if (IsKeyPressed(KEY_SPACE)) DrawRectangle(sliderX, GetScreenHeight() - 55, 15, 30, WHITE);
    sliderX += sliderSpeed * 0.5;
    if (sliderX > 1100) sliderSpeed = sliderSpeed * - 1;
    if (sliderX < 350) sliderSpeed = sliderSpeed * - 1;
}
