// updated 2/7/18

#include "GLScene.h"
#include <GLLight.h>
#include <Inputs.h>
#include "Parallax.h"
#include "DeltaTime.h"
#include <Player.h>
#include <Skybox.h>


//Model *modelTeapot = new Model();
Inputs *keyboardAndMouse = new Inputs();
Model *ground = new Model(3.33, 0.2, -2.0, -1.1, "ground");
Model *block = new Model(1.0, 0.5, 1.0, -0.5, "block");
Player *testPlayer = new Player();

DeltaTime* dTime = new DeltaTime();
//Skybox* sky = new Skybox();
// Can create multiple Parallax objects to create parallaxed backgrounds
Parallax *plx = new Parallax();

GLScene::GLScene()
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    movableObjects.push_back(testPlayer);

    staticObjects.push_back(block);
    staticObjects.push_back(ground);
}

GLScene::~GLScene()
{
}

// Static Variables for use in player class to check collision
vector<Model*> GLScene::movableObjects;
vector<Model*> GLScene::staticObjects;

// initialize our graphic settings for our scene
GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH); // Shading mode
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // set background color to black
    glClearDepth(1.0f); // depth buffer
    glEnable(GL_DEPTH_TEST); // test to see what's in front and what's in back
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL); // allows texture to have color
    GLLight Light(GL_LIGHT0);

    // Initialize Models Here
    cout << "Parallax Initializing" << endl;
    plx->ParallaxInit("Images/background.jpg");

    block->InitModel("Images/Block.png", true);
    ground->InitModel("Images/Block.png", true);
    dTime ->UpdateDeltaTime();

//    sky->LoadTextures();

    testPlayer->InitPlayer();
    return true;
}

GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

//    glPushMatrix();
////    glScaled(3.33, 3.33, 1);
//    sky->DrawBox();
//    glPopMatrix();
    glPushMatrix();
    glScaled(3.33, 3.33, 1);
    plx->DrawSquare(screenWidth, screenHeight); // draw background
    glPopMatrix();

    glPushMatrix(); // remove push/pop if you want things to interact with each other in the renderer
    block->DrawModel();
    glPopMatrix();

    glPushMatrix();
    ground->DrawModel();
    glPopMatrix();

    testPlayer->Update();


//    glTranslatef(testPlayer->GetX(), testPlayer->GetY(), 0);
//    gluLookAt(testPlayer->GetX(), testPlayer->GetY(), -10.0, testPlayer->GetX(), testPlayer->GetY(), -1.0, 0, 1.0, 100.0);

    dTime->UpdateDeltaTime();
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
            keyboardAndMouse->KeyPressed(testPlayer);
            keyboardAndMouse->KeyEnv(plx, 0.1);
            break;

        case WM_KEYUP:
            keyboardAndMouse->wParam = wParam;
            keyboardAndMouse->KeyUp(testPlayer);
            break;

        case WM_MOUSEMOVE:
            keyboardAndMouse->wParam = wParam;
            keyboardAndMouse->MouseDown(testPlayer, LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_MOUSEWHEEL:
            keyboardAndMouse->WheelMove(testPlayer, GET_WHEEL_DELTA_WPARAM(wParam));
            break;

//        case WM_LBUTTONDOWN:
//            keyboardAndMouse->MouseDown(modelTeapot, LOWORD(lParam), HIWORD(lParam));
//            break;

        case WM_RBUTTONDOWN:
            break;
	}
}
