#include "Inputs.h"
#include <iostream>
#include "DeltaTime.h"

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

    switch(wParam)
    {
        case aKey:
            model->Move(-1.0);
//            model->xPos -= 0.1 * (model->acceleration+=0.098);
//            model->direction = "left";
//            cout << model->xPos << endl;
            break;
        case dKey:
            model->Move(1.0);
//            model->xPos += 0.1 * (model->acceleration+=0.098);
            break;
        case VK_SPACE:
            model->SetJump(true);
            //model->Update();


            break;
        case cKey: //Resets model coordinates to (0,0) and resets acceleration to 0.
            model->acceleration = 0.0;
            model->xPos = 0.0;
            model->yPos = 0.0;
            cout << "Acceleration and location reset" << endl;
            break;
        case bKey:
            model->NormalAttack(true);
            break;
//        case VK_LEFT:
//            model->rotateX += 1.0;
//            break;
//        case VK_RIGHT:
//            model->rotateX -= 1.0;
//            break;
//        case VK_DOWN:
//            model->rotateY -= 1.0;
//            break;
//        case VK_UP:
//            model->rotateY += 1.0;
//            break;
//        case VK_ADD:
//            model->zoom += 1.0;
//            break;
//        case VK_SUBTRACT:
//            model->zoom -= 1.0;
//            break;
//        case VK_MBUTTON:
//            model->zoom += wParam;
//            break;
    }
}

void Inputs::KeyUp(Model* model)
{
    const int aKey = 0x41, dKey = 0x44, cKey = 0x43, bKey = 0x42;
    switch(wParam)
    {
        case aKey:
            model->SlowDown();
            break;
        case dKey:
            model->SlowDown();
            break;
    }
}

void Inputs::MouseDown(Model* model, double xNew, double yNew)
{
    double currentX = xNew - prevMouseX;
    double currentY = yNew - prevMouseY;

    if(wParam == VK_LBUTTON)
    {
//        if(currentX > 1.0) currentX = 5.0;
//        if(currentX < -1.0) currentX = -5.0;
//        if(currentY > 1.0) currentY = 5.0;
//        if(currentY < -1.0) currentY = -5.0;

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
