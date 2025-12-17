#pragma once
#include "raylib-cpp.hpp"
#include "Entity.hpp"

class Arrow : public Entity {

    public:

    Arrow();
    Arrow(const AnimatedSprite &sprite, float maxSpeed);

    void spawn(raylib::Vector2 position, raylib::Vector2 direction);

    void update(float deltaTime) override;


};


