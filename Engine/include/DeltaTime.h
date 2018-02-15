#ifndef DELTATIME_H
#define DELTATIME_H


class DeltaTime
{
    public:
        static int deltaTime;
        DeltaTime();
        virtual ~DeltaTime();
        void UpdateDeltaTime();


    protected:

    private:
        int oldTime;
        int newTime;
};

#endif // DELTATIME_H
