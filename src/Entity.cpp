
#include "class/Entity.hpp"

Entity::Entity() : position(100, 100), speed(0, 0), acceleration(0,0), sprite(AnimatedSprite()), radius(20), maxSpeed(100) {

}

bool Entity::isColliding(Entity const *targetEntity) {
    // NOTE : The colliding check is true when the center of one of them is inside the other one (or under the radius distance of the other one)
    if ( CheckCollisionCircles(position, radius, targetEntity->position, targetEntity->radius)) return true;
    else return false;
}

void Entity::update(float deltaTime) {
    this->sprite.update(deltaTime);
}

void Entity::draw() {
    this->sprite.draw(this->position);
}

void Entity::drawHitbox() {
    raylib::Color color = raylib::Color(0, 0, 120, 100);
    DrawCircle(this->position.x, this->position.y, this->radius, color);
}
