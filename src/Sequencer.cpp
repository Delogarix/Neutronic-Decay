
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
        std::string type = this->events.front().type;
        unsigned int amount = this->events.front().amount;
        //std::cout << type << " * " << amount << std::endl;

        if (owner != nullptr) owner->spawnBullets(type, amount);
        this->events.pop();
    }

}
