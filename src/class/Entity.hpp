#pragma once
#include "AnimatedSprite.hpp"
#include "raylib-cpp.hpp"

class Entity {

    public:

    raylib::Vector2 position, speed, acceleration;
    AnimatedSprite sprite;
    float maxSpeed;


    Entity();

    virtual void update(float deltaTime) ;

    virtual void draw();
};

