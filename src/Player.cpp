
#include "class/Player.hpp"

#include <iostream>

#include "raylib-cpp.hpp"

void Player::onReceivingHit() {
    if (!invcFrameTime.active) { 
        this->health--;
        invcFrameTime.activate();
        PlaySound(hitSound);
    }
}

void Player::onGivingHit() {

}

Player::Player() : isMoving(false), health(11), worldLimit(GetScreenHeight()), accelerationScale(500), invcFrameTime(Timer(0.5, 0))  {
    this->radius = 14;
    this->position = raylib::Vector2(GetScreenWidth()/2, GetScreenHeight()/2);
}

Player::Player(const AnimatedSprite &sprite, int worldLimit) : isMoving(false), health(5), worldLimit(worldLimit - 23),accelerationScale(500), invcFrameTime(Timer(0.5, 0)) {
    this->sprite = sprite;
    this->radius = 14;
    this->position = raylib::Vector2(GetScreenWidth()/2, GetScreenHeight()/2);
    hitSound = LoadSound("assets/hit1.wav");
}

bool Player::isDead() { return this->health < 1; }

unsigned int Player::getHeath() const { return this->health; }


void Player::handleInputs(float deltaTime) {
    isMoving = false;
    #if defined(PLATFORM_WEB)
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){ position.x +=  accelerationScale * deltaTime; isMoving = true;} // Right
    if (IsKeyDown(KEY_Q) || IsKeyDown(KEY_LEFT)) { position.x += -accelerationScale * deltaTime; isMoving = true;} // Left
    if (IsKeyDown(KEY_Z) || IsKeyDown(KEY_UP))   { position.y += -accelerationScale * deltaTime; isMoving = true;} // Up
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) { position.y +=  accelerationScale * deltaTime; isMoving = true;} // Down
    #else
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){ position.x +=  accelerationScale * deltaTime; isMoving = true;} // Right
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) { position.x += -accelerationScale * deltaTime; isMoving = true;} // Left
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))   { position.y += -accelerationScale * deltaTime; isMoving = true;} // Up
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) { position.y +=  accelerationScale * deltaTime; isMoving = true;} // Down
    #endif
}

void Player::spawn(raylib::Vector2 position, raylib::Vector2 direction) {
    this->position = position;
    
}

void Player::update(float deltaTime) {
    handleInputs(deltaTime);
    collideWithBorder(worldLimit, raylib::Vector2(GetScreenWidth()/2, GetScreenHeight()/2));
    Entity::update(deltaTime);
    invcFrameTime.update();
    //std::cout << position.x - GetScreenWidth()/2 << " : " << position.y - GetScreenHeight()/2 << std::endl;
}
