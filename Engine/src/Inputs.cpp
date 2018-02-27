#include "Inputs.h"
#include <iostream>

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
            model->xPos -= 0.1 * (model->acceleration+=0.098);
//            plx->Scroll(true, "left", 1);
            cout << model->xPos << endl;
            break;
        case dKey:
            model->xPos += 0.1 * (model->acceleration+=0.098);
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

void Inputs::KeyUp()
{

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
     model->zoom += (delta / 120); // 120 is the default WHEEL_DELTA value in windows.h. HThis will constrain zoom to +/- 1.0
}
