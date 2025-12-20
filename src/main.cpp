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

bool freeze = false;

float sliderX, sliderSpeed;

const unsigned int MAXOBJECTS1 = 50000;
std::array<Entity *, MAXOBJECTS1> objects;

Sequencer sequencer;
std::string waveFileName = "wave/wave1.txt";

raylib::Window window(screenWidth, screenHeight, "Project: Neutronic Decay");
raylib::Texture2D iridiumTex = LoadTexture("assets/iridium-core.png");
raylib::Texture2D redArrowTex = LoadTexture("assets/red-arrow.png");
raylib::Texture2D homingElecTex = LoadTexture("assets/homing-elec.png");
AnimatedSprite iridium = AnimatedSprite(&iridiumTex, 6, 0, 3.6f, 5, 1);
AnimatedSprite redArrow = AnimatedSprite(&redArrowTex, 2, PI/4, 9.5f, 5, 1);
AnimatedSprite homingElec = AnimatedSprite(&homingElecTex, 2, 0, 13.0f, 7, 1);

Player player(iridium);

Game game;

int getFreeIndex();
void resolveCollision(Entity *player, Entity *&bullet);
void drawActionBar();
void drawSlider();
void bulletRandomWave(Entity *target);

void init() {
    for (int i = 0; i < MAXOBJECTS; i++) { objects[i] = nullptr; }
    objects[0] = &player;
    sliderX = 400;
    sliderSpeed = 1;
    sequencer = Sequencer(waveFileName, nullptr);
    sequencer.start();
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

    sequencer.update(GetFrameTime());

    if (IsKeyPressed(KEY_P)) freeze = !freeze;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        //bulletRandomWave(&player);
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        int i = getFreeIndex();
        objects[i] = new Homing(homingElec, &player);
        objects[i]->spawn(GetMousePosition(), getRandomVector());
    }

    player.update(GetFrameTime());
    for (unsigned int i = 1; i < MAXOBJECTS; i++) {
        if (objects[i] != nullptr && !freeze) {
            objects[i]->update(GetFrameTime());
            resolveCollision(&player, objects[i]);
        }
    }


    BeginDrawing(); // - - - - - DRAW PART - - - - - //

    window.ClearBackground(RAYWHITE);

    for (unsigned int i = 0; i < MAXOBJECTS; i++) {
        if (objects[i] != nullptr) {
            objects[i]->draw();
            //objects[i]->drawHitbox();
        }
    }

    game.draw();

    drawActionBar();
    drawSlider();

    DrawFPS(30, 30);

    EndDrawing();
}

int getFreeIndex() {
    for (int i = 0; i < MAXOBJECTS1; i++) {
        if (objects[i] == nullptr) {
            return i;
        }
    }
    std::cout << "No more space in objects lists!" << std::endl;
    return -1;
}

void resolveCollision(Entity *player, Entity *&bullet) {
    if (bullet != nullptr && player->isColliding(bullet)) {
        delete bullet;
        bullet = nullptr;
    }
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

void bulletRandomWave(Entity *target) {

    raylib::Vector2 spawnPoint, targetDirection;
    int side = GetRandomValue(0, 3); // LEFT - UP - RIGHT - DOWN
    int bulletType = GetRandomValue(0, 2);
    if (side == 0) spawnPoint = raylib::Vector2(0, GetRandomValue(0, GetScreenHeight()));
    if (side == 1) spawnPoint = raylib::Vector2(GetRandomValue(0, GetScreenWidth()), 0);
    if (side == 2) spawnPoint = raylib::Vector2(GetScreenWidth(), GetRandomValue(0, GetScreenHeight()));
    if (side == 3) spawnPoint = raylib::Vector2(GetRandomValue(0, GetScreenWidth()), GetScreenHeight());
    targetDirection = target->position - spawnPoint;

    int i = getFreeIndex();
    if (bulletType != 0) objects[i] = new Arrow(redArrow, 900);
    else objects[i] = new Homing(homingElec, target);

    objects[i]->spawn(spawnPoint, targetDirection);
}