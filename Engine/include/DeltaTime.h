#ifndef DELTATIME_H
#define DELTATIME_H


class DeltaTime
{
    public:
        DeltaTime();
        virtual ~DeltaTime();
        static double GetDeltaTime();
        void UpdateDeltaTime();

    protected:

    private:
        double oldTime;
};

#endif // DELTATIME_H
