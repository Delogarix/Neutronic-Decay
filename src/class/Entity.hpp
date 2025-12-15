#pragma once
#include "AnimatedSprite.hpp"
#include "raylib-cpp.hpp"

enum CollisionSystem {
    EMPTY = 0,
    ENEMIES = 1,
    PLAYER = 2
};

class Entity {

    public:

    raylib::Vector2 position, speed, acceleration;
    AnimatedSprite sprite;
    float maxSpeed;

    public:

    Entity();

    virtual void update(float deltaTime);

    virtual void draw();
};

