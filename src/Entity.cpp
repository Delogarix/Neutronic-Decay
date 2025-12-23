
#include "class/Entity.hpp"

#include <iostream>

void Entity::onReceivingHit() {

}

void Entity::onGivingHit() {

}

void Entity::collideWithBorder(float border, raylib::Vector2 offset) {
    if (position.x > border + offset.x) position.x = border + offset.x;
    if (position.x < -border + offset.x) position.x = - border + offset.x;
    if (position.y > border + offset.y)  position.y = border + offset.y;
    if (position.y < -border + offset.y) position.y = - border + offset.y;
}

Entity::Entity() : position(100, 100), speed(0, 0), acceleration(0,0), radius(20), maxSpeed(100), lifeTime(Timer(0, false)), sprite(AnimatedSprite()) {

}

Entity::~Entity() = default;

raylib::Vector2 Entity::getPosition() const { return this->position; }

bool Entity::lifeTimeExceeded() const { return (this->lifeTime.signal >= 1); }

bool Entity::isColliding(Entity const *targetEntity) {
    // NOTE : The colliding check is true when the center of one of them is inside the other one (or under the radius distance of the other one)
    if ( CheckCollisionCircles(position, radius, targetEntity->position, targetEntity->radius)) return true;
    else return false;
}

void Entity::update(float deltaTime) {
    this->sprite.update(deltaTime);
    this->lifeTime.update();
}

void Entity::draw() {
    this->sprite.draw(this->position);
}

void Entity::drawHitbox() {
    raylib::Color color = raylib::Color(125, 120, 120, 125);
    DrawCircle(this->position.x, this->position.y, this->radius, color);
}
