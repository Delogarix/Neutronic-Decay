#pragma once
#include "raylib-cpp.hpp"
#include <fstream>
#include <queue>


class Game;

struct Event {
    float timeCode;
    std::string type;
    unsigned int amount;
    std::string side;
};

class Sequencer {

    std::queue<Event> events;
    std::string fileName;
    float startTime, passedTime, timeToWin;
    bool hasStarted;
    Game *owner;



    public:

    Sequencer();
    Sequencer(std::string fileName, Game *owner);

    bool levelDone();
    float getTimeElapsed();

    void readFile(std::string fileName);

    void start();
    void reStart();

    void update(float deltaTime);

};

