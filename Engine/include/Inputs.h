#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <iostream>
#include <Model.h>
#include <Parallax.h>

class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();

        void KeyPressed(Model*);
        void KeyUp();
        void KeyEnv(Parallax*, float); // movements of background

        void MouseDown(Model*, double, double);
        void MouseUp();
        void WheelMove(Model*, double);
        int GetDeltaTime();

        double prevMouseX, prevMouseY;

        WPARAM wParam;

    protected:

    private:
};

#endif // INPUTS_H
