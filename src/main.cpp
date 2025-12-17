#include <iostream>
#include <array>
#include "../include/raylib-cpp.hpp"
#include "class/AnimatedSprite.hpp"
#include "class/Entity.hpp"
#include "class/Player.hpp"
#include "class/Arrow.hpp"
#include "class/Homing.hpp"

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

int screenWidth = 1500;
int screenHeight = 800;

const unsigned int maxObjects = 50000;
std::array<Entity *, maxObjects> objects;

raylib::Window window(screenWidth, screenHeight, "Project: Neutronic Decay");
raylib::Texture2D iridiumTex = LoadTexture("assets/iridium-core.png");
raylib::Texture2D redArrowTex = LoadTexture("assets/red-arrow.png");
raylib::Texture2D homingElecTex = LoadTexture("assets/homing-elec.png");
AnimatedSprite iridium = AnimatedSprite(&iridiumTex, 8, 0, 3.6f, 5, 1);
AnimatedSprite redArrow = AnimatedSprite(&redArrowTex, 4, PI/4, 9.5f, 5, 1);
AnimatedSprite homingElec = AnimatedSprite(&homingElecTex, 1, 0, 13.0f, 7, 1);

Player player(iridium);
Arrow arrow(redArrow, 900);
Homing electron(homingElec, &player);

int getFreeIndex();

void init() {
    player.position = raylib::Vector2(GetScreenWidth()/2, GetScreenHeight()/2);

    for (int i = 0; i < maxObjects; i++) {
        objects[i] = nullptr;
    }

    objects[0] = &player;
    objects[1] = &arrow;
    objects[2] = &electron;
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

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        int i = getFreeIndex();
        objects[i] = new Arrow(redArrow, 900);
        objects[i]->spawn(GetMousePosition(), getRandomVector());
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        int i = getFreeIndex();
        objects[i] = new Homing(homingElec, &player);
        objects[i]->spawn(GetMousePosition(), getRandomVector());
    }

    for (unsigned int i = 0; i < maxObjects; i++) {
        if (objects[i] != nullptr) {
            objects[i]->update(GetFrameTime());
        }
    }

    BeginDrawing(); // - - - - - DRAW PART - - - - - //

    window.ClearBackground(RAYWHITE);

    DrawText("Welcome to neutronic-decay !", 220, 200, 20, DARKGREEN);
    for (unsigned int i = 0; i < maxObjects; i++) {
        if (objects[i] != nullptr) {
            objects[i]->draw();
        }
    }

    DrawFPS(30, 30);

    EndDrawing();
}

int getFreeIndex() {
    for (int i = 0; i < maxObjects; i++) {
        if (objects[i] == nullptr) {
            std::cout << "i : " << i << std::endl;
            return i;
        }
    }
    std::cout << "No more space in objects lists!" << std::endl;
    return -1;
}