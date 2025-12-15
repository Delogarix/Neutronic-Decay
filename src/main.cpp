#include <iostream>
#include "../include/raylib-cpp.hpp"
#include "class/AnimatedSprite.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// WEB Cmd
/*
 * em++ -o game.html main.cpp -Os -Wall ../lib/Web/libraylib.a -I. -I ../include -L. -s USE_GLFW=3 --shell-file ../shell/shell.html -DPLATFORM_WEB
 */

void UpdateDrawFrame();

int screenWidth = 800;
int screenHeight = 450;

raylib::Window window(screenWidth, screenHeight, "Project: Neutronic Decay");
raylib::Texture2D iridiumTex = LoadTexture("assets/iridium-core.png");
AnimatedSprite iridium = AnimatedSprite(&iridiumTex, 5, 0, 3.6f, 5, 1);


class Player {
    public:

    raylib::Vector2 position;
    float radius;
    float speed;
    bool isMoving;
    AnimatedSprite sprite;

    Player() {
        position = raylib::Vector2(0, 0);
        radius = 20;
        isMoving = false;
        speed = 5;
        sprite = AnimatedSprite();
    }

    void update(float deltaTime) {
        handleInputs(deltaTime);
    }

    void draw() {
        DrawCircle(position.x, position.y, radius, DARKGREEN);
    }

    void handleInputs(float deltaTime) {
        isMoving = false;
        if (IsKeyDown(KEY_D)) { position.x += speed; isMoving = true;}  // Right
        if (IsKeyDown(KEY_A)) { position.x += -speed; isMoving = true;} // Left
        if (IsKeyDown(KEY_W)) { position.y += -speed; isMoving = true;} // Up
        if (IsKeyDown(KEY_S)) { position.y += speed; isMoving = true;}  // Down
    }

};

Player player;

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
    iridium.update(GetFrameTime());

    BeginDrawing();

    window.ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    player.draw();
    iridium.draw(player.position);

    // Object methods.

    EndDrawing();
}