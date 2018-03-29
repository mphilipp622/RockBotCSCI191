#include <Inputs.h>
#include <iostream>
#include <DeltaTime.h>
#include <string>

using namespace std;


Inputs::Inputs()
{
}

Inputs::~Inputs()
{
}

void Inputs::KeyPressed(Player* model)
{
    // Handle key presses for model passed to this function
    const int aKey = 0x41, dKey = 0x44, cKey = 0x43, bKey = 0x42;

    // Use the unordered map of booleans to keep track of which keys are pressed. This allows multiple keys being pressed at once
    if(!keys["MoveLeft"] && wParamKeys == aKey)
    {
        model->StartMove(-1.0);
        keys["MoveLeft"] = true;
    }
    if(!keys["MoveRight"] && wParamKeys == dKey)
    {
        model->StartMove(1.0);
        keys["MoveRight"] = true;
    }
    if (!keys["Jump"] && wParamKeys == VK_SPACE)
    {
        model->StartJump();
        keys["Jump"] = true;
    }
    if(!keys["PlayChord"] && wParamKeys == VK_SHIFT)
    {
        model->PlayChords(true);
        keys["PlayChord"] = true;
    }
}

void Inputs::KeyUp(Player* model)
{
    const int aKey = 0x41, dKey = 0x44, cKey = 0x43, bKey = 0x42;

    if(keys["MoveLeft"] && wParamKeys == aKey)
    {
        model->SlowDown();
        keys["MoveLeft"] = false;
    }
    if (keys["MoveRight"] && wParamKeys == dKey)
    {
        model->SlowDown();
        keys["MoveRight"] = false;
    }
    if(keys["Jump"] && wParamKeys == VK_SPACE)
    {
        keys["Jump"] = false;
    }
    if(keys["PlayChord"] && wParamKeys == VK_SHIFT)
    {
        model->PlayChords(false);
        keys["PlayChord"] = false;
    }
}

void Inputs::MouseDown(Player* model, LPARAM lParam)
{
    // using 0x5 for lmouse and 0x6 for rmouse. For some reason, windows is sending those values when shift is held down instead of 0x1 and 0x2
    if(keys["PlayChord"] && wParamMouse == 0x5)
    {
        model->CheckUserInput(0);
        // convert mouse X and Y to openGL coordinates
//        double screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
//        double screenWidth = GetSystemMetrics(SM_CXSCREEN); //
//        double aspectRatio = screenWidth / screenHeight;
//        mousePosX = (LOWORD(lParam) / (screenWidth / 2) - 1.0) * aspectRatio * 3.33;
//        mousePosY = -(HIWORD(lParam) / (screenHeight / 2) - 1.0) * 3.33;
//        model->ShootProjectile(mousePosX, mousePosY);
//        model->rotateX += currentY;
//        model->rotateY += currentX;
    }
    if(keys["PlayChord"] && wParamMouse == 0x6)
        model->CheckUserInput(1);


//    prevMouseX = xNew;
//    prevMouseY = yNew;
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

//    const int aKey = 0x41, dKey = 0x44;
//
//    switch(wParam)
//    {
//    case aKey:
//        plx->xMin -= speed * DeltaTime::GetDeltaTime();
//        plx->xMax -= speed * DeltaTime::GetDeltaTime();
//        break;
//    case dKey:
//        plx->xMin += speed * DeltaTime::GetDeltaTime();
//        plx->xMax += speed * DeltaTime::GetDeltaTime();
//        break;
//    case VK_UP:
//        plx->yMin -= speed * DeltaTime::GetDeltaTime();
//        plx->yMax -= speed * DeltaTime::GetDeltaTime();
//        break;
//    case VK_DOWN:
//        plx->yMin += speed * DeltaTime::GetDeltaTime();
//        plx->yMax += speed * DeltaTime::GetDeltaTime();
//        break;
//    }
}


void Inputs::SetKey(string keyName, bool status)
{
    // allow the player class to set status of a key. This is used to avoid input locking when collision happens
    keys[keyName] = status;
}


void Inputs::SetMousePointer(double x, double y)
{
    mousePosX = x;
    mousePosY = y;
}
