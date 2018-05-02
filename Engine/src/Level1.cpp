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

GLint Level1::initGL()
{

}

GLint Level1::drawGLScene()
{

}

int Level1::windowsMsg(HWND, UINT, WPARAM, LPARAM)
{

}

void Level1::LoadScene(string name)
{

}
