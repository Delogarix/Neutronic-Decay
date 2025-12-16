
#include "class/Player.hpp"
#include "raylib-cpp.hpp"

Player::Player() : isMoving(false), accelerationScale(1)  {
}

Player::Player(const AnimatedSprite &sprite) : isMoving(false), accelerationScale(500) {
    this->sprite = sprite;
}


void Player::handleInputs(float deltaTime) {
    isMoving = false;
    #if defined(PLATFORM_WEB)
    if (IsKeyDown(KEY_D)) { position.x +=  accelerationScale * deltaTime; isMoving = true;} // Right
    if (IsKeyDown(KEY_Q)) { position.x += -accelerationScale * deltaTime; isMoving = true;} // Left
    if (IsKeyDown(KEY_Z)) { position.y += -accelerationScale * deltaTime; isMoving = true;} // Up
    if (IsKeyDown(KEY_S)) { position.y +=  accelerationScale * deltaTime; isMoving = true;} // Down
    #else
    if (IsKeyDown(KEY_D)) { position.x +=  accelerationScale * deltaTime; isMoving = true;} // Right
    if (IsKeyDown(KEY_A)) { position.x += -accelerationScale * deltaTime; isMoving = true;} // Left
    if (IsKeyDown(KEY_W)) { position.y += -accelerationScale * deltaTime; isMoving = true;} // Up
    if (IsKeyDown(KEY_S)) { position.y +=  accelerationScale * deltaTime; isMoving = true;} // Down
    #endif
}

void Player::update(float deltaTime) {
    handleInputs(deltaTime);
    Entity::update(deltaTime);
}
