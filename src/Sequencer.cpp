
#include "class/Sequencer.hpp"
#include "class/Game.hpp"
#include <iostream>

float Sequencer::getTimeElapsed() { return passedTime - this->startTime; }

void Sequencer::flush() {
    std::queue<Event> empty;
    events.swap(empty);
}

void Sequencer::reload() {
    this->events = this->savedEvents;
    this->warnings = this->savedWarnings;
}

Sequencer::Sequencer() : fileName("wave/wave1.txt"), startTime(GetTime()), passedTime(0), hasStarted(false), owner(nullptr) { }

Sequencer::Sequencer(Game *owner) : fileName("wave/wave1.txt"), startTime(GetTime()), passedTime(0), hasStarted(false), owner(owner) { }

Sequencer::Sequencer(std::string fileName, Game *owner) : fileName(fileName), startTime(GetTime()), passedTime(0), hasStarted(false), owner(owner) {
    this->readFileDelta(fileName);
}

bool Sequencer::levelDone() { return getTimeElapsed() >= timeToWin; }

void Sequencer::readFile(std::string fileName) {
    this->fileName = fileName;
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
            this->savedEvents.push(inputEvent);
        }
    }
    this->timeToWin = this->savedEvents.back().timeCode + 5.0f;
}

void Sequencer::readFileDelta(std::string fileName) {
    this->fileName = fileName;
    flush();
    std::ifstream stream(fileName);
    if (!stream.is_open()) {
        std::cout << "ERROR: cannot open file " << fileName << std::endl;
    }
    else {
        Event inputEvent;
        float timecodeCount = 0.0f;
        float timeDelta = 0.0f;
        while (stream.good()) {
            stream >> timeDelta;
            stream >> inputEvent.type;
            stream >> inputEvent.amount;
            stream >> inputEvent.side;
            timecodeCount += timeDelta;
            inputEvent.timeCode = timecodeCount;
            this->savedEvents.push(inputEvent);
        }
        this->timeToWin = timecodeCount + 5.0f;
    }
    std::cout << "Time to win : " << this->timeToWin <<  std::endl;
}

void Sequencer::append(std::string fileName) {
    std::ifstream stream(fileName);
    if (!stream.is_open()) {
        std::cout << "ERROR: cannot open append file " << fileName << std::endl;
    }
    else {
        Event inputEvent;
        float timecodeCount = this->savedEvents.back().timeCode;
        float timeDelta = 0.0f;
        while (stream.good()) {
            stream >> timeDelta;
            stream >> inputEvent.type;
            stream >> inputEvent.amount;
            stream >> inputEvent.side;
            timecodeCount += timeDelta;
            this->timeToWin += timeDelta;
            inputEvent.timeCode = timecodeCount;
            this->savedEvents.push(inputEvent);
        }
    }
    std::cout << "Time to win : " << this->timeToWin <<  std::endl;
}

void Sequencer::writeFile(float offset) { // offset all the timecodes
    std::string outputFile = "wave/warning.txt";
    std::ofstream stream;
    stream.open(outputFile);
    if (!stream) {
        std::cout << "Erreur avec l'écriture du fichier : " << outputFile << std::endl;
    }
    else {
        std::queue<Event> copyEventQueue = savedEvents;
        while (!copyEventQueue.empty()) {
            Event event = copyEventQueue.front();
            event.timeCode -= offset;
            stream << event.timeCode << " " << event.type << " " << event.amount << " " << event.side << "\n";
            copyEventQueue.pop();
        }
    }
}

void Sequencer::readFileWarnings(std::string fileName) {
    this->fileName = fileName;
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
            this->savedWarnings.push(inputEvent);
        }
    }
}


void Sequencer::stop() {
    this->hasStarted = false;
    this->startTime = 0;
    this->passedTime = 0;
    this->reload();
}

void Sequencer::start() {
    this->startTime = 0;
    this->passedTime = 0;
    this->hasStarted = true;
    this->reload();
}

void Sequencer::update(float deltaTime) {
    if (hasStarted) {
        passedTime += deltaTime;
        if (!this->events.empty() && this->getTimeElapsed() > this->events.front().timeCode) {
            std::string type = this->events.front().type;

            if (owner != nullptr) {
                owner->spawnBullets(events.front());
            }
            this->events.pop();
        }
        while (!this->warnings.empty() && this->getTimeElapsed() > this->warnings.front().timeCode) {
            
            if (owner != nullptr) {
                owner->queueWarning(warnings.front());
            }
            this->warnings.pop();
        }
    }
}
