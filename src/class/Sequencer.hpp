#pragma once
#include "raylib-cpp.hpp"
#include <fstream>
#include <queue>

enum ProjectileType {
    ARROW = 0,
    HOMING = 1,
    BOULDER = 2
};

struct Event {
    float timeCode;
    std::string type;
    unsigned int amount;
};

class Sequencer {

    std::queue<Event> events;
    float startTime;
    bool hasStarted;

    float getTimeElapsed();

    public:

    Sequencer();
    Sequencer(std::string fileName);

    void readFile(std::string fileName);

    void start();

    void update(float deltaTime);

};

