#include <iostream>
#include "../include/raylib-cpp.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame();

int screenWidth = 800;
int screenHeight = 450;

raylib::Window window(screenWidth, screenHeight, "Project: Neutronic Decay");

class Player {
    public:

    raylib::Vector2 position;
    float radius;
    float speed;
    bool isMoving;

    Player() {
        position = raylib::Vector2(0, 0);
        radius = 20;
        isMoving = false;
        speed = 5;
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

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}

void UpdateDrawFrame() {

    player.update(GetFrameTime());

    BeginDrawing();

    window.ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    player.draw();
    // Object methods.

    EndDrawing();
}