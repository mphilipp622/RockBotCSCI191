#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <iostream>
#include <Model.h>
#include <Parallax.h>
#include <unordered_map>
#include <string>
#include <Player.h>

class Player;

class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();

        void KeyPressed(Player*);
        void KeyUp(Player* model);
        void KeyEnv(Parallax*, float); // movements of background

<<<<<<< HEAD
        void MouseDown(Player*, double, double);
        void MouseUp();
        void WheelMove(Player*, double);
=======
        void MouseDown(Player*, LPARAM lParam);
        void MouseUp();
        void WheelMove(Player*, double);
        void SetMousePointer(double x, double y);
>>>>>>> master

        double prevMouseX, prevMouseY;

        void SetKey(string keyName, bool status);
        WPARAM wParamKeys, wParamMouse;

    protected:

    private:
        std::unordered_map<std::string, bool> keys;
<<<<<<< HEAD
=======
        double mousePosX, mousePosY;
>>>>>>> master
};

#endif // INPUTS_H
