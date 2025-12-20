#pragma once
#include "raylib-cpp.hpp"
#include <fstream>
#include <queue>


class Game;

struct Event {
    float timeCode;
    std::string type;
    unsigned int amount;
};

class Sequencer {

    std::queue<Event> events;
    float startTime;
    bool hasStarted;
    Game *owner;

    float getTimeElapsed();

    public:

    Sequencer();
    Sequencer(std::string fileName, Game *owner);

    void readFile(std::string fileName);

    void start();

    void update(float deltaTime);

};

