#pragma once
#include "Entity.hpp"

class Player : public Entity {

    bool isMoving;
    float accelerationScale;

    public:

    Player();
    Player(const AnimatedSprite &sprite);

    void handleInputs(float deltaTime);
    void spawn(raylib::Vector2 position, raylib::Vector2 direction) override;
    void update(float deltaTime) override;

};

