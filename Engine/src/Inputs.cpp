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
    }
}

void Inputs::KeyUp()
{

}

void Inputs::MouseDown(Model* model, double xNew, double yNew)
{
    double currentX = xNew - prevMouseX;
    double currentY = xNew - prevMouseY;

    if(wParam == VK_LBUTTON)
    {

        std::cout << xNew << "    " << prevMouseX << "    " << currentX << std::endl;
        if(currentX > 1.0) currentX = 1.0;
        if(currentX < -1.0) currentX = -1.0;
        if(currentY > 1.0) currentY = 1.0;
        if(currentY < -1.0) currentY = -1.0;
//        model->rotateY += currentX / 10;
//        model->rotateX += currentY / 10;
        model->rotateX += currentY;
        model->rotateY += currentX;
//        if(currentX <= -1)
//        model->rotateY -= 1.0;
//        else if(currentX >= 1)
//            model->rotateY += 1.0;
//        if(currentY <= -1)
//            model->rotateX -= 1.0;
//        else if(currentY >= 1)
//            model->rotateX += 1.0;
    }

    prevMouseX = xNew;
    prevMouseY = yNew;
}

void Inputs::MouseUp()
{

}
