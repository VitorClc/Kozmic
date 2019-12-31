#pragma once

#include <SDL.h>

class Timer
{
    private:
    int startTicks;
    
    int pausedTicks;
    
    bool paused;
    bool started;
    
    public:
    Timer();
    
    void Start();
    void Stop();
    void Pause();
    void Unpause();
    
    int GetTicks();
    
    bool IsStarted();
    bool IsPaused();    
};