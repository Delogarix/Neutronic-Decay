
#include "class/Arrow.hpp"

Arrow::Arrow() { }

Arrow::Arrow(const AnimatedSprite &sprite, float maxSpeed) {
    this->sprite = sprite;
    this->maxSpeed = maxSpeed;
    radius = 5;
}

void Arrow::spawn(raylib::Vector2 position, raylib::Vector2 direction) {
    this->position = position;
    this->speed = direction.Normalize().Scale(maxSpeed);
    this->sprite.lookAt(this->speed);
}

void Arrow::update(float deltaTime) {
    Entity::update(deltaTime);
    this->position = this->position + this->speed.Scale(deltaTime);
}
