#include "Inputs.h"

Inputs::Inputs()
{
}

Inputs::~Inputs()
{
}

void Inputs::KeyPressed(Model* model)
{
    // Handle key presses for model passed to this function
    switch(wParam)
    {
        case VK_LEFT:
//            model->xPos -= 0.1;
            model->rotateX += 1.0;
            break;
        case VK_RIGHT:
            model->rotateX -= 1.0;
            break;
        case VK_DOWN:
            model->rotateY -= 1.0;
            break;
        case VK_UP:
            model->rotateY += 1.0;
            break;
        case VK_ADD:
            model->zoom += 1.0;
            break;
        case VK_SUBTRACT:
            model->zoom -= 1.0;
            break;
        case VK_MBUTTON:
            model->zoom += wParam;
            break;
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
