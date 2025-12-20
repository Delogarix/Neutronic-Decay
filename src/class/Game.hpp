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
    Player player;

    Sequencer sequencer;

    unsigned int getFreeIndex();

    void resolveCollision(Entity* player, Entity *&bullet);


    public:

    Game();

    void init(); // Texture management

    void update(float deltaTime);

    void draw();

    void bulletRandomWave(Entity *target);


    // ------------------ //

    Entity* convertTypeToBullet(std::string type);
    void spawnBullet(Entity* bullet);
    void spawnBullets(std::string type, unsigned int amount);

    static raylib::Vector2 getRandomVector();
    static raylib::Vector2 offsetVectorAngle(const raylib::Vector2 &sourceVec, float angle); // offset a vector direction within a max angle in degree

};
