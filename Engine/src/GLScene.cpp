// updated 2/7/18

#include "GLScene.h"
#include "GLLight.h"
#include <Model.h>
#include <Inputs.h>
#include "Parallax.h"
#include "DeltaTime.h"

Model *modelTeapot = new Model();
Inputs *keyboardAndMouse = new Inputs();
Parallax *plx = new Parallax();

GLScene::GLScene()
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen
}

GLScene::~GLScene()
{

}

// initialize our graphic settings for our scene
GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH); // Shading mode
    glClearColor(0, 0, 0, 0); // set background color to black
    glClearDepth(1.0); // depth buffer
    glEnable(GL_DEPTH_TEST); // test to see what's in front and what's in back
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL); // allows texture to have color
    GLLight Light(GL_LIGHT0);

    // Initialize Models Here
    cout << "Model Initializing" << endl;
    modelTeapot->InitModel("Images/MilkyWay.jpg");
    cout << "Parallax Initializing" << endl;
    plx->ParallaxInit("Images/background.jpg");
    return true;
}

GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    modelTeapot->DrawModel(); // render teapot
    glPopMatrix();

    glScaled(3.33, 3.33, 1);
    glPushMatrix();

    plx->DrawSquare(screenWidth, screenHeight); // draw background
    glPopMatrix();

    plx->Scroll(false, "up", 1);
    //modelTeapot->Update(); // Will eventuall be replaced with an array of models. Will iterate each one and update
}

GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat) width / (GLfloat) height;

    glViewport(0, 0, width, height); // window for our game
    glMatrixMode(GL_PROJECTION); // set the projection type for 3D space
    glLoadIdentity(); // loads identity matrix
    gluPerspective(45.0, aspectRatio, 0.1, 100); // 45 degree angle, aspect ratio, 0.1 near to 100 far. Sets the perspective of our renderer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // loads identity matrix for modelview

}
int GLScene::windowsMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)									// Check For Windows Messages
	{
        case WM_KEYDOWN:
            keyboardAndMouse->wParam = wParam;
            keyboardAndMouse->KeyPressed(modelTeapot);
            break;

        case WM_KEYUP:
            keyboardAndMouse->wParam = wParam;
            keyboardAndMouse->KeyUp();
            break;

        case WM_MOUSEMOVE:
            keyboardAndMouse->wParam = wParam;
            keyboardAndMouse->MouseDown(modelTeapot, LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_MOUSEWHEEL:
            keyboardAndMouse->WheelMove(modelTeapot, GET_WHEEL_DELTA_WPARAM(wParam));
            break;

//        case WM_LBUTTONDOWN:
//            keyboardAndMouse->MouseDown(modelTeapot, LOWORD(lParam), HIWORD(lParam));
//            break;

        case WM_RBUTTONDOWN:
            break;
	}
}
