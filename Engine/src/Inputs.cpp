#include "Inputs.h"
#include <iostream>
#include "DeltaTime.h"
#include <string>

using namespace std;


Inputs::Inputs()
{
}

Inputs::~Inputs()
{
}

float acceleration = 0.0;
//Global variable for acceleration, might want to
//implement into the model class later on.
void Inputs::KeyPressed(Player* model)
{
    // Handle key presses for model passed to this function
    const int aKey = 0x41, dKey = 0x44, cKey = 0x43, bKey = 0x42;

    // Use the unordered map of booleans to keep track of which keys are pressed. This allows multiple keys being pressed at once
    if(!keys["MoveLeft"] && wParam == aKey)
    {
        model->StartMove(-1.0);
        keys["MoveLeft"] = true;
    }
    if(!keys["MoveRight"] && wParam == dKey)
    {
        model->StartMove(1.0);
        keys["MoveRight"] = true;
    }
    if (!keys["Jump"] && wParam == VK_SPACE)
    {
        model->StartJump();
        keys["Jump"] = true;
    }
}

void Inputs::KeyUp(Player* model)
{
    const int aKey = 0x41, dKey = 0x44, cKey = 0x43, bKey = 0x42;

    if(keys["MoveLeft"] && wParam == aKey)
    {
        model->SlowDown();
        keys["MoveLeft"] = false;
    }
    if (keys["MoveRight"] && wParam == dKey)
    {
        model->SlowDown();
        keys["MoveRight"] = false;
    }
    if(keys["Jump"] && wParam == VK_SPACE)
    {
        keys["Jump"] = false;
    }
}

void Inputs::MouseDown(Player* model, double xNew, double yNew)
{
    double currentX = xNew - prevMouseX;
    double currentY = yNew - prevMouseY;

    if(wParam == VK_LBUTTON)
    {
        model->rotateX += currentY;
        model->rotateY += currentX;
    }

    prevMouseX = xNew;
    prevMouseY = yNew;
}

void Inputs::MouseUp()
{

}

void Inputs::WheelMove(Player* model, double delta)
{
     model->zoom += (delta / 120); // 120 is the default WHEEL_DELTA value in windows.h. This will constrain zoom to +/- 1.0
}
void Inputs::KeyEnv(Parallax* plx, float speed)
{
    // handles background scrolling based on key inputs

    const int aKey = 0x41, dKey = 0x44;

    switch(wParam)
    {
    case aKey:
        plx->xMin -= speed * DeltaTime::GetDeltaTime();
        plx->xMax -= speed * DeltaTime::GetDeltaTime();
        break;
    case dKey:
        plx->xMin += speed * DeltaTime::GetDeltaTime();
        plx->xMax += speed * DeltaTime::GetDeltaTime();
        break;
    case VK_UP:
        plx->yMin -= speed * DeltaTime::GetDeltaTime();
        plx->yMax -= speed * DeltaTime::GetDeltaTime();
        break;
    case VK_DOWN:
        plx->yMin += speed * DeltaTime::GetDeltaTime();
        plx->yMax += speed * DeltaTime::GetDeltaTime();
        break;
    }
}
