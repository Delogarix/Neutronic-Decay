
#include "class/Sequencer.hpp"
#include "class/Game.hpp"
#include <iostream>

float Sequencer::getTimeElapsed() { return GetTime() - this->startTime; }

Sequencer::Sequencer() :startTime(GetTime()), hasStarted(false), owner(nullptr) { }

Sequencer::Sequencer(std::string fileName, Game *owner) : startTime(GetTime()), hasStarted(false), owner(owner) {
    this->readFile(fileName);
}

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
            this->events.push(inputEvent);
        }
    }
}

void Sequencer::start() {
    this->startTime = GetTime();
    this->hasStarted = true;
}

void Sequencer::update(float deltaTime) {

    if (!this->events.empty() && this->getTimeElapsed() > this->events.front().timeCode) {
        std::cout << this->events.front().type << " * " << this->events.front().amount << std::endl;
        // game->spawnBullets(std::string type, unsigned int amount);
        if (owner != nullptr) owner->bulletRandomWave(&owner->player);
        this->events.pop();
    }

}
