#include "Level1.h"

Level1::Level1()
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    sceneName = "Level1";
}

Level1::~Level1()
{
    //dtor
}
