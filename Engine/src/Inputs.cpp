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

void Inputs::MouseDown(Model*, double, double)
{

}

void Inputs::MouseUp()
{

}
