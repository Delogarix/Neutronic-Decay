#pragma once
#include "Entity.hpp"

class Homing : public Entity {

    Entity *target;
    float attractForce;

    public:

    Homing();
    Homing(const AnimatedSprite &sprite, Entity *target);

    void spawn(raylib::Vector2 position, raylib::Vector2 direction) override;

    void update(float deltaTile) override;

};


