#pragma once
#include "raylib-cpp.hpp"
#include "Entity.hpp"

class Arrow : public Entity {

    public:

    Arrow();
    Arrow(const AnimatedSprite &sprite, float maxSpeed);
    Arrow(const AnimatedSprite &sprite, float maxSpeed, float radius);

    void spawn(raylib::Vector2 position, raylib::Vector2 direction) override;

    void update(float deltaTime) override;


};


