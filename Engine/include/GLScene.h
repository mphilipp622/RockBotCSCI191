// updated 2/7/18

#ifndef GLSCENE_H
#define GLSCENE_H

#include <windows.h>
#include <glut.h>
#include <iostream>
#include <vector>
#include <Model.h>
<<<<<<< HEAD
=======
#include <Inputs.h>
>>>>>>> master

using namespace std;

class GLScene
{
    public:
        GLScene();
        virtual ~GLScene();
        GLint initGL();
        GLint drawGLScene();
        GLvoid resizeGLScene(GLsizei, GLsizei);

        int windowsMsg(HWND, UINT, WPARAM, LPARAM);

        WPARAM wParam;
        float screenHeight, screenWidth;

        static vector<Model*> movableObjects; // only moving objects will check for collision
        static vector<Model*> staticObjects; // environmental, non-moving objects don't need to check for collision
<<<<<<< HEAD

=======
        static Inputs *keyboardAndMouse;

        static void UpdateModelPositions();
>>>>>>> master
    protected:

    private:
};

#endif // GLSCENE_H
