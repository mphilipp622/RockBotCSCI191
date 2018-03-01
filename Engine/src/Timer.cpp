#include "Timer.h"

Timer::Timer()
{
    startedAt = 0;
    pausedAt = 0;
    paused = false;
    started = false;
}

Timer::~Timer()
{
    //dtor
}

bool Timer::IsStarted()
{
    return started;
}

bool Timer::IsStopped()
{
    return !started;
}

bool Timer::IsPaused()
{
    return paused;
}

void Timer::Pause()
{
    if(paused || !started)
        return;
    paused = true;
    pausedAt = clock(); // set paused time
}

void Timer::Resume()
{
    if(!paused)
        return;
    paused = false;
    startedAt += clock() - pausedAt; // get current time
}

void Timer::Stop()
{
    started = false;
}

void Timer::Reset()
{
    paused = false;
    startedAt = clock();
}

void Timer::Start()
{
    if(started)
        return;

    started = true;
    paused = false;
    startedAt = clock();
}


clock_t Timer::GetTicks()
{
    if(!started)
        return 0;

    if(paused)
        return pausedAt - startedAt;

    return clock() - startedAt;
}
