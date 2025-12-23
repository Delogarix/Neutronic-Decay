#pragma once
#include "AnimatedSprite.hpp"
#include "raylib-cpp.hpp"
#include "Timer.hpp"

class Entity {

    protected:

    raylib::Vector2 position, speed, acceleration;
    float radius, maxSpeed;
    Timer lifeTime;

    void collideWithBorder(float border, raylib::Vector2 offset);

    public:

    AnimatedSprite sprite;

    Entity();
    virtual ~Entity();

    raylib::Vector2 getPosition() const;
    bool lifeTimeExceeded() const;
    bool isColliding(Entity const *targetEntity); // (const) le pointeur ne peux pas pointer une autre ressource

    virtual void onReceivingHit();

    virtual void onGivingHit();

    virtual void spawn(raylib::Vector2 position, raylib::Vector2 direction) = 0;

    virtual void update(float deltaTime);

    virtual void draw();
    void drawHitbox();
};

