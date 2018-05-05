#include "Trigger.h"

Trigger::Trigger()
{
    //ctor
}

Trigger::Trigger(double newX, double newY, double newWidth, double newHeight, string newText, string newTag)
{
    xPos = newX;
    yPos = newY;
    width = newWidth;
    height = newHeight;
    tag = newTag;
    text = newText;
}

Trigger::~Trigger()
{
    //dtor
}

double Trigger::GetX()
{
    return xPos;
}

double Trigger::GetY()
{
    return yPos;
}

double Trigger::GetWidth()
{
    return width;
}

double Trigger::GetHeight()
{
    return height;
}

string Trigger::GetTag()
{
    return tag;
}
