
#include "class/Entity.hpp"

Entity::Entity() : position(100, 100), speed(0, 0), acceleration(0,0), sprite(AnimatedSprite()), maxSpeed(100) {

}

void Entity::update(float deltaTime) {
    this->sprite.update(deltaTime);
}

void Entity::draw() {
    this->sprite.draw(this->position);
}
