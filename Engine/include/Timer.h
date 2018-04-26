#ifndef TIMER_H
#define TIMER_H

#include <time.h>

class Timer
{
    public:
        Timer();
        virtual ~Timer();

        clock_t startedAt;
        clock_t pausedAt;

        bool started;
        bool paused;

        bool IsStarted();
        bool IsStopped();
        bool IsPaused();

        void Pause();
        void Resume();
        void Stop();
        void Start();

        void Reset();

        clock_t GetTicks(); // milliseconds
        clock_t GetTime();

    protected:

    private:
};

#endif // TIMER_H
