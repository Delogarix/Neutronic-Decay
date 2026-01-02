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
    raylib::Vector2 leftCorner, rightCorner, topRight, bottomLeft;
    bool isFreezed, isOnMenu, isOnTransition;
    Timer transitionTime;

    raylib::Texture2D iridiumTex, homingElecTex, redArrowTex, boulderTex;
    AnimatedSprite iridiumS, redArrowS, homingElecS, boulderS;
    Sound hitSound, deathSound, winSound;

    std::array<Entity *, MAXOBJECTS> objects;
    Player player;

    Sequencer sequencer;
    std::queue<Event> warnings;

    unsigned int getFreeIndex();

    void flushObjects();
    void resolveCollision(Entity* player, Entity *&bullet);
    void displayGameInfo();
    void drawFrame();
    void reset();
    void start();
    void sendScore();
    void startTransition();
    void drawWarningSide(Event event);

    public:

    Game();

    void init(); // Texture management

    void update(float deltaTime);

    void draw();

    // ------------------ //

    Entity* convertTypeToBullet(std::string type);
    raylib::Vector2 convertSideToVector(std::string side);
    std::string getRandomSide();
    raylib::Color colorFromType(std::string type);
    raylib::Vector2 centerFromSide(std::string side);
    raylib::Vector2 dimensionFromEvent(Event event);

    void spawnBullet(Entity* bullet, Event event);
    void spawnBullets(Event event);
    void queueWarning(Event event);

    static raylib::Vector2 getRandomVector();
    static raylib::Vector2 offsetVectorAngle(const raylib::Vector2 &sourceVec, float angle); // offset a vector direction within a max angle in degree
    static raylib::Rectangle rectangleFromCenterPoint(raylib::Vector2 center, float width, float height);
};
