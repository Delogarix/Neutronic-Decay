#pragma once

class Timer {

public:
    float duration, startTime; // in seconds
    bool active, isLooping;
    int signal;

    // - - - - - CONSTRUCTORS - - - - - 

    Timer();
    Timer(float duration, bool shouldRepeat);
    Timer(float nduration, bool shouldRepeat, bool shouldStartNow);

    // - - - - - METHODS - - - - -

    bool timerDone();

    void resetSignal();

    float getTimeElapsed();

    float getTimeRemaining();

    void activate();

    void deactivate();

    void update();

};