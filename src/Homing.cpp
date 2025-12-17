#include "class/Homing.hpp"

Homing::Homing() : target(nullptr), attractForce(5) { }

Homing::Homing(const AnimatedSprite &sprite, Entity *target) : target(target), attractForce(1500) {
    this->sprite = sprite;
    maxSpeed = 600;
}

void Homing::spawn(raylib::Vector2 position, raylib::Vector2 direction) {
    this->position = position;
    this->speed = direction.Normalize().Scale(maxSpeed);
}

void Homing::update(float deltaTime) {
    Entity::update(deltaTime);
    raylib::Vector2 targetDirection = target->position - this->position;
    this->speed += targetDirection.Normalize().Scale(this->attractForce * deltaTime);
    this->position += this->speed * deltaTime;
    if (this->speed.Length() > this->maxSpeed) this->speed = this->speed.Normalize().Scale(this->maxSpeed);
}
