// updated 2/7/18

#include <LoadShader.h>
#include <GLScene.h>
#include <GLLight.h>
#include <Parallax.h>
#include <DeltaTime.h>
#include <Player.h>
#include <Skybox.h>
#include <Timer.h>

//Model *modelTeapot = new Model();
Model *ground = new Model(6.0, 0.3, 0, -1.0, "ground", "Environment");
Model *block = new Model(2.0, 0.2, 3.0, 0, "block", "Environment");
Model *block2 = new Model(2.0, 0.2, -0.5, 1.0, "block2", "Environment");
//MeleeEnemy* testEnemy;
//Skybox* sky = new Skybox();
// Can create multiple Parallax objects to create parallaxed backgrounds
Parallax *plx = new Parallax();
Timer *sceneTimer = new Timer();

GLScene::GLScene()
{
    isLoaded = false;
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

//    testEnemy = new MeleeEnemy(0.7, 0.7, 2, 0.5, "TestEnemy");
}

GLScene::~GLScene()
{
}

// Static Variables for use in player class to check collision
vector<Model*> GLScene::movableObjects;
vector<Model*> GLScene::staticObjects;
vector<Enemy*> GLScene::enemies;

// static input for player to use as well
Inputs* GLScene::keyboardAndMouse;

// initialize our graphic settings for our scene
GLint GLScene::initGL()
{
    glewInit();
    audioEngine = new AudioEngine();
    player = new Player(0.0, 5);
    testEnemy = new MeleeEnemy(0.7, 3, 0.8, 0.8, "Enemy");

    keyboardAndMouse = new Inputs();
    sceneTimer->Start();

    glShadeModel(GL_SMOOTH); // Shading mode
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // set background color to black
    glClearDepth(1.0f); // depth buffer
    glEnable(GL_DEPTH_TEST); // test to see what's in front and what's in back
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL); // allows texture to have color
    GLLight Light(GL_LIGHT0);

    // Initialize Models Here
    cout << "Parallax Initializing" << endl;
    plx->ParallaxInit("Images/BGSciFi.jpg");

    block->InitModel("Images/Block.png", true);
    block2->InitModel("Images/Block2.png", true);
    ground->InitModel("Images/Block.png", true);

    movableObjects.push_back(player);
    enemies.push_back(testEnemy);
//    movableObjects.push_back(testEnemy);

    staticObjects.push_back(block);
    staticObjects.push_back(ground);
    staticObjects.push_back(block2);

//    sky->LoadTextures();

    player->InitPlayer();
    Player::player = player;
    testEnemy->InitEnemy();

    BGM = new AudioSource("Music", "Audio/Music/BGM/DrumLoop.wav",0, 0, .8, true);
    BGM->PlayMusic();
    dTime = new DeltaTime();
    return true;
}

GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(player->GetX(), player->GetY(), 6.0,
            player->GetX(), player->GetY(), player->GetZoom(),
            0.0f, 1.0f, 0.0f);
//    glPushMatrix();
////    glScaled(3.33, 3.33, 1);
//    sky->DrawBox();
//    glPopMatrix();
    glPushMatrix();
    glScaled(12, 12, 1);
    plx->DrawSquare(screenWidth, screenHeight); // draw background
    glPopMatrix();

    for(auto& model : staticObjects)
        model->DrawModel();

    for(auto& enemy : enemies)
        enemy->Update();

    for(auto& model : movableObjects)
        model->Update();


    dTime->UpdateDeltaTime();

	return 1;
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
    if(uMsg == WM_KEYDOWN)
    {
//        testAudio->UpdatePosition();

//        testAudio->Update();
//        testAudio->Play();
//        PlaySound("Audio/Music/ab9.wav", NULL, SND_ASYNC);
        keyboardAndMouse->wParamKeys = wParam;
        keyboardAndMouse->KeyPressed(player);
        keyboardAndMouse->KeyEnv(plx, 0.1);
    }
    if(uMsg == WM_KEYUP)
    {
        keyboardAndMouse->wParamKeys = wParam;
        keyboardAndMouse->KeyUp(player);
    }
    if(uMsg == WM_MOUSEMOVE)
    // should constantly update mouse pointer x and y positions
        keyboardAndMouse->SetMousePointer(LOWORD(lParam), HIWORD(lParam));
    if(uMsg == WM_LBUTTONDOWN)
    {
        // left-click functionality
        keyboardAndMouse->wParamMouse = wParam;
        keyboardAndMouse->MouseDown(player, lParam);
    }
    if(uMsg == WM_RBUTTONDOWN)
    {
        keyboardAndMouse->wParamMouse = wParam;
        keyboardAndMouse->MouseDown(player, lParam);
    }
    if(uMsg == WM_MOUSEWHEEL)
        keyboardAndMouse->WheelMove(player, GET_WHEEL_DELTA_WPARAM(wParam));

	return 1;
}

void GLScene::SetLoaded(bool newState)
{
    isLoaded = newState;
}
