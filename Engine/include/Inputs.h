#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <iostream>
#include <Model.h>
#include <Parallax.h>
#include <unordered_map>
#include <string>

class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();

        void KeyPressed(Model*);
        void KeyUp(Model* model);
        void KeyEnv(Parallax*, float); // movements of background

        void MouseDown(Model*, double, double);
        void MouseUp();
        void WheelMove(Model*, double);

        double prevMouseX, prevMouseY;

        WPARAM wParam;

    protected:

    private:
        std::unordered_map<std::string, bool> keys;
};

#endif // INPUTS_H
