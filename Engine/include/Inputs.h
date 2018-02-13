#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <iostream>
#include <Model.h>

class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();

        void KeyPressed(Model*);
        void KeyUp();
        void MouseDown(Model*, double, double);
        void MouseUp();

        double prevMouseX, prevMouseY;

        WPARAM wParam;

    protected:

    private:
};

#endif // INPUTS_H
