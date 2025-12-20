#pragma once
#include <array>
#include <raylib-cpp.hpp>
#include "Entity.hpp"
#include "Player.hpp"
#include "Arrow.hpp"
#include "Homing.hpp"
#include <iostream>

#include "Sequencer.hpp"

const unsigned int MAXOBJECTS = 50000;

class Game {

    int boxLength;
    bool isFreezed;

    raylib::Texture2D iridiumTex, homingElecTex, redArrowTex, boulderTex;
    AnimatedSprite iridiumS, redArrowS, homingElecS, boulderS;

    std::array<Entity *, MAXOBJECTS> objects;


    Sequencer sequencer;

    unsigned int getFreeIndex();

    void resolveCollision(Entity* player, Entity *&bullet);


    public:
    Player player;
    Game();

    void init(); // Texture managnment

    void update(float deltaTime);

    void draw();

    void bulletRandomWave(Entity *target);

};
