#pragma once
#include "AnimatedSprite.hpp"
#include "raylib-cpp.hpp"

class Entity {

    public:

    raylib::Vector2 position, speed, acceleration;
    AnimatedSprite sprite;
    float radius, maxSpeed;


    Entity();

    bool isColliding(Entity const *targetEntity); // le pointeur ne peux pas pointer une autre ressource

    virtual void spawn(raylib::Vector2 position, raylib::Vector2 direction) = 0;

    virtual void update(float deltaTime) ;

    virtual void draw();
    void drawHitbox();
};

