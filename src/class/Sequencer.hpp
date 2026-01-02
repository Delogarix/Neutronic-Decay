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

    std::queue<Event> savedEvents;
    std::queue<Event> events;
    std::queue<Event> savedWarnings;
    std::queue<Event> warnings;
    std::string fileName;
    float startTime, passedTime, timeToWin;
    bool hasStarted;
    Game *owner;

    void flush();
    void reload();

    public:

    Sequencer();
    Sequencer(Game *owner);
    Sequencer(std::string fileName, Game *owner);

    bool levelDone();
    float getTimeElapsed();

    void readFile(std::string fileName);
    void readFileDelta(std::string fileName);
    void append(std::string fileName);
    void writeFile(float offset);
    void readFileWarnings(std::string fileName);

    void stop();
    void start();

    void update(float deltaTime);

};

