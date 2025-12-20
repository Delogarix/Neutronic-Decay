#include "class/Timer.hpp"
#include "raylib-cpp.hpp"

// - - - - - CONSTRUCTORS - - - - - 

Timer::Timer() : duration(1), startTime(0), active(false), isLooping(true), signal(0)
{ }

Timer::Timer(float duration, bool shouldRepeat) : duration(duration), startTime(0), active(false), isLooping(shouldRepeat), signal(0)
{ }

Timer::Timer(float duration, bool shouldRepeat, bool shouldStartNow) : duration(duration), startTime(0), active(shouldStartNow), isLooping(shouldRepeat), signal(0)
{ }

// - - - - - METHODS - - - - -

bool Timer::timerDone() { return (signal >= 1); }

void Timer::resetSignal() { signal = 0; }

float Timer::getTimeElapsed() { return (GetTime() - startTime); }

float Timer::getTimeRemaining() { return ( duration - getTimeElapsed() ); }

void Timer::activate() {
    active = true;
    startTime = GetTime();
}


void Timer::deactivate() {
    active = false;
    startTime = 0;
    signal++;
    if ( signal > 1) signal = 0;
}

void Timer::update() {
    if (active) {
        float currentTime = GetTime();
        if ( currentTime - startTime >= duration) {
            deactivate();
            
            if (isLooping) { activate(); }
        }
    }
}

