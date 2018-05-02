// updated 2/7/18

#include <GLScene.h>
#include <Parallax.h>
#include <DeltaTime.h>
#include <Player.h>
#include <Timer.h>
#include <HUD.h>
#include <GLLight.h>

GLScene::GLScene()
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    sceneName = "Game";
//    testEnemy = new MeleeEnemy(0.7, 0.7, 2, 0.5, "TestEnemy");
}

GLScene::GLScene(string newName)
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    sceneName = newName;
}


GLScene::~GLScene()
{
}

// Static Variables for use in player class to check collision
vector<Model*> GLScene::movableObjects;
vector<Model*> GLScene::staticObjects;
vector<Enemy*> GLScene::enemies;

// initialize our graphic settings for our scene
GLint GLScene::initGL()
{
    player = new Player(0.0, 0);
    testEnemy = new MeleeEnemy(0.7, 3, 0.8, 0.8, "Enemy");
    displayHUD = new HUD();
    testRangedEnemy = new RangedEnemy(1, 3, 1, 1, "Enemy");

    keyboardAndMouse = new Inputs();
    sceneTimer = new Timer();

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
    background = new Parallax();
    background->ParallaxInit("Images/Backgrounds/BGSciFi.jpg");

    enemies.push_back(testEnemy);
    enemies.push_back(testRangedEnemy);
//    movableObjects.push_back(testEnemy);

    Model* tempBlock = new Model(2.0, 0.2, 3.0, 0, "block", "Environment");
    tempBlock->InitModel("Images/Platforms/Block.png", true);
    staticObjects.push_back(tempBlock);

    tempBlock = new Model(6.0, 0.3, 0, -1.0, "ground", "Environment");
    tempBlock->InitModel("Images/Platforms/Block.png", true);
    staticObjects.push_back(tempBlock);

    tempBlock = new Model(2.0, 0.2, -0.5, 1.0, "block2", "Environment");
    tempBlock->InitModel("Images/Platforms/Block2.png", true);
    staticObjects.push_back(tempBlock);

    player->InitPlayer();
    Player::player = player;

    for(auto& enemy : enemies)
        enemy->InitEnemy();

//    testEnemy->InitEnemy();
//    testRangedEnemy->InitEnemy();

//    shader->ShaderInit("Shaders/v.vs", "Shaders/f.fs");
//    shader->ShaderInit("Shaders/v1.vs", "Shaders/f1.fs");

//    testShader->BindTexture("Images/MilkyWay.jpg");
    BGM = new AudioSource("Music", "Audio/Music/BGM/DrumLoop.wav",0, 0, .8, true);
    BGM->PlayMusic();
    dTime = new DeltaTime();
    return true;
}

GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(player->GetX(), player->GetY(), 6,
            player->GetX(), player->GetY(), player->GetZoom(),
            0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glScaled(12, 12, 1);
    background->DrawSquare(screenWidth, screenHeight); // draw background
    glPopMatrix();

    displayHUD->showHP(Player::player);
    
	for(auto& model : movableObjects)
        model->Update();

    for(auto& model : staticObjects)
        model->DrawModel();

    for(auto& enemy : enemies)
        enemy->Update();

    Player::player->Update();

    dTime->UpdateDeltaTime();

	return 1;
}

GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat) width / (GLfloat) height;

    glViewport(0, 0, width, height); // window for our game
    glMatrixMode(GL_PROJECTION); // set the projection type for 3D space
    glLoadIdentity(); // loads identity matrix
//    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
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
//        keyboardAndMouse->KeyEnv(background, 0.1);
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

string GLScene::GetSceneName()
{
    return sceneName;
}

void GLScene::LoadScene(string name)
{
    return;
}

bool GLScene::CheckPointerCollision(Model* button, double mouseX, double mouseY)
{
    // Check to see if the user's mouse pointer has overlapped with the button's collider.

    // get model boundaries

    // Don't know where these constant values came from. Eyeballed the coordinates of my mouse and took the difference due to the z-position versus screen coordinates.
    double minX = (button->GetX() - button->GetWidth() / 2); // 0.198148
    double maxX = (button->GetX() + button->GetWidth() / 2);
    double minY = (button->GetY() - button->GetHeight() / 2); // old value 0.0694444 .0963542
    double maxY = (button->GetY() + button->GetHeight() / 2); // 0572917

    return Overlap (mouseX, minX, maxX) && Overlap (mouseY, minY, maxY);
}

bool GLScene::Overlap(double pos, double min, double max)
{
    return pos >= min && pos <= max;
}

void GLScene::CleanStaticData()
{
    if(enemies.size() > 0)
        enemies.clear();

    if(movableObjects.size() > 0)
        movableObjects.clear();

    if(staticObjects.size() > 0)
        staticObjects.clear();
}
