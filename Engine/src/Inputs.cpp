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
void Inputs::KeyPressed(Model* model)
{
    // Handle key presses for model passed to this function
    const int aKey = 0x41, dKey = 0x44, cKey = 0x43, bKey = 0x42;

    // Use the unordered map of booleans to keep track of which keys are pressed. This allows multiple keys being pressed at once
    if(!keys["a"] && wParam == aKey)
    {
        model->StartMove(-1.0);
        keys["a"] = true;
    }
    if(!keys["d"] && wParam == dKey)
    {
        model->StartMove(1.0);
        keys["d"] = true;
    }
    if (!keys["space"] && wParam == VK_SPACE)
    {
        model->StartJump();
        keys["space"] = true;
    }
}

void Inputs::KeyUp(Model* model)
{
    const int aKey = 0x41, dKey = 0x44, cKey = 0x43, bKey = 0x42;

    if(keys["a"] && wParam == aKey)
    {
        model->SlowDown();
        keys["a"] = false;
    }
    if (keys["d"] && wParam == dKey)
    {
        model->SlowDown();
        keys["d"] = false;
    }
    if(keys["space"] && wParam == VK_SPACE)
    {
        keys["space"] = false;
    }
}

void Inputs::MouseDown(Model* model, double xNew, double yNew)
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

void Inputs::WheelMove(Model* model, double delta)
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
