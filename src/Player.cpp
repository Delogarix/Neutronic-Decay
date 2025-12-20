
#include "class/Player.hpp"
#include "raylib-cpp.hpp"

void Player::onReceivingHit() {
    this->health--;
}

void Player::onGivingHit() {

}

Player::Player() : isMoving(false), health(11), accelerationScale(500)  {
    this->radius = 14;
    this->position = raylib::Vector2(GetScreenWidth()/2, GetScreenHeight()/2);
}

Player::Player(const AnimatedSprite &sprite) : isMoving(false), health(11), accelerationScale(500) {
    this->sprite = sprite;
    this->radius = 14;
    this->position = raylib::Vector2(GetScreenWidth()/2, GetScreenHeight()/2);
}

bool Player::isDead() { return this->health < 1; }

unsigned int Player::getHeath() const { return this->health; }


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

void Player::spawn(raylib::Vector2 position, raylib::Vector2 direction) {
    this->position = position;
}

void Player::update(float deltaTime) {
    handleInputs(deltaTime);
    Entity::update(deltaTime);
}
