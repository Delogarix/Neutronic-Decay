
#include "class/Sequencer.hpp"

#include <iostream>

float Sequencer::getTimeElapsed() { return GetTime() - this->startTime; }

Sequencer::Sequencer() :startTime(GetTime()), hasStarted(false) { }

Sequencer::Sequencer(std::string fileName) : startTime(GetTime()), hasStarted(false) {
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
        this->events.pop();
    }

}
