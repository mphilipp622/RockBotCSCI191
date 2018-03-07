#include "DeltaTime.h"
#include <windows.h>
#include <glut.h>
#include <iostream>

double deltaTime = 0.0;

DeltaTime::DeltaTime()
{
    oldTime = glutGet(GLUT_ELAPSED_TIME);
    UpdateDeltaTime();
}

DeltaTime::~DeltaTime()
{
    //dtor
}
void DeltaTime::UpdateDeltaTime()
{
    double time = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (time - oldTime) / 1000.0;
    oldTime = time;

//    glutPostRedisplay();
}
double DeltaTime::GetDeltaTime()
{
    return deltaTime;
}
