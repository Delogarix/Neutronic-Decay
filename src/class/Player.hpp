#pragma once
#include "Entity.hpp"

class Player : public Entity {

    bool isMoving;
    float accelerationScale;

    public:

    Player();
    Player(const AnimatedSprite &sprite);

    void handleInputs(float deltaTime);

    void update(float deltaTime) override;

};

