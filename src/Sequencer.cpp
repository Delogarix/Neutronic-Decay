
#include "class/Sequencer.hpp"
#include "class/Game.hpp"
#include <iostream>

float Sequencer::getTimeElapsed() { return passedTime - this->startTime; }

Sequencer::Sequencer() : fileName("wave/wave1.txt"), startTime(GetTime()), passedTime(0), hasStarted(false), owner(nullptr) { }

Sequencer::Sequencer(std::string fileName, Game *owner) : fileName(fileName), startTime(GetTime()), passedTime(0), hasStarted(false), owner(owner) {
    this->readFile(fileName);

}

bool Sequencer::levelDone() { return getTimeElapsed() >= timeToWin; }

void Sequencer::readFile(std::string fileName) {
    std::ifstream stream(fileName);
    if (!stream.is_open()) {
        std::cout << "ERROR: cannot open file " << fileName << std::endl;
    }
    else {
        Event inputEvent;
        while (stream.good()) {
            stream >> inputEvent.timeCode;
            stream >> inputEvent.type;
            stream >> inputEvent.amount;
            stream >> inputEvent.side;
            this->events.push(inputEvent);
        }
    }
    this->timeToWin = this->events.back().timeCode + 10.0f;
}

void Sequencer::stop() {
    this->hasStarted = false;
}

void Sequencer::start() {
    this->startTime = 0;
    this->passedTime = 0;
    this->hasStarted = true;
}

void Sequencer::reStart() {
    std::queue<Event> empty;
    events.swap(empty);
    readFile(this->fileName);
    start();
    std::cout << "Restarting wave : " << fileName << std::endl;
}

void Sequencer::update(float deltaTime) {
    if (hasStarted) {
        passedTime += deltaTime;
        if (!this->events.empty() && this->getTimeElapsed() > this->events.front().timeCode) {
            std::string type = this->events.front().type;

            if (owner != nullptr) owner->spawnBullets(events.front());
            this->events.pop();
        }
    }
}
