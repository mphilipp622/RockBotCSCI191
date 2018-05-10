#include <DeltaTime.h>
#include <windows.h>
#include <glut.h>
#include <iostream>

double DeltaTime::deltaTime;

DeltaTime::DeltaTime()
{
    deltaTime = 0.0;
    oldTime = glutGet(GLUT_ELAPSED_TIME);
    UpdateDeltaTime();

}

DeltaTime::~DeltaTime()
{
    //dtor
    deltaTime = 0.0;
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
