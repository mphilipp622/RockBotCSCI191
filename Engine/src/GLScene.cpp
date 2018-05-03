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
    ClearStaticData();
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
//    player = new Player(0.0, 0);
//    testEnemy = new MeleeEnemy(0.7, 3, 0.8, 0.8, "Enemy");

//    testRangedEnemy = new RangedEnemy(1, 3, 1, 1, "Enemy");

    glShadeModel(GL_SMOOTH); // Shading mode
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // set background color to black
    glClearDepth(1.0f); // depth buffer
    glEnable(GL_DEPTH_TEST); // test to see what's in front and what's in back
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL); // allows texture to have color
    GLLight Light(GL_LIGHT0);

    LoadLevelFromXML();

    displayHUD = new HUD();
    keyboardAndMouse = new Inputs();
    sceneTimer = new Timer();

    sceneTimer->Start();



    // Initialize Models Here
//    cout << "Parallax Initializing" << endl;
//    background = new Parallax();
//    background->ParallaxInit("Images/Backgrounds/BGSciFi.jpg");
//
//    enemies.push_back(testEnemy);
//    enemies.push_back(testRangedEnemy);
////    movableObjects.push_back(testEnemy);
//
//    Model* tempBlock = new Model(2.0, 0.2, 3.0, 0, "block", "Environment");
//    tempBlock->InitModel("Images/Platforms/Block.png", true);
//    staticObjects.push_back(tempBlock);
//
//    tempBlock = new Model(6.0, 0.3, 0, -1.0, "ground", "Environment");
//    tempBlock->InitModel("Images/Platforms/Block.png", true);
//    staticObjects.push_back(tempBlock);
//
//    tempBlock = new Model(2.0, 0.2, -0.5, 1.0, "block2", "Environment");
//    tempBlock->InitModel("Images/Platforms/Block2.png", true);
//    staticObjects.push_back(tempBlock);
//
//    player->InitPlayer();
//    Player::player = player;
//
//    for(auto& enemy : enemies)
//        enemy->InitEnemy();

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

    gluLookAt(Player::player->GetX(), Player::player->GetY(), 6.0,
            Player::player->GetX(), Player::player->GetY(), Player::player->GetZoom(),
            0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glScaled(backgroundScaleX, backgroundScaleY, 1);
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
        keyboardAndMouse->KeyPressed(Player::player);
//        keyboardAndMouse->KeyEnv(background, 0.1);
    }
    if(uMsg == WM_KEYUP)
    {
        keyboardAndMouse->wParamKeys = wParam;
        keyboardAndMouse->KeyUp(Player::player);
    }
    if(uMsg == WM_MOUSEMOVE)
    // should constantly update mouse pointer x and y positions
        keyboardAndMouse->SetMousePointer(LOWORD(lParam), HIWORD(lParam));
    if(uMsg == WM_LBUTTONDOWN)
    {
        // left-click functionality
        keyboardAndMouse->wParamMouse = wParam;
        keyboardAndMouse->MouseDown(Player::player, lParam);
    }
    if(uMsg == WM_RBUTTONDOWN)
    {
        keyboardAndMouse->wParamMouse = wParam;
        keyboardAndMouse->MouseDown(Player::player, lParam);
    }
    if(uMsg == WM_MOUSEWHEEL)
        keyboardAndMouse->WheelMove(Player::player, GET_WHEEL_DELTA_WPARAM(wParam));

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

void GLScene::ConvertMouseToWorld(double mouseX, double mouseY, double cameraX, double cameraY, double &xOut, double &yOut)
{
    double modelMatrix[16];
    double projMatrix[16];
    GLint viewport[4];
    GLfloat newX, newY, newZ;

    glGetDoublev(GL_MODELVIEW_MATRIX,modelMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX,projMatrix);
    glGetIntegerv(GL_VIEWPORT,viewport);

    newX = (float) mouseX;
    newY = (float) viewport[3] - (GLfloat) mouseY - 1;

    glReadPixels( newX, float(newY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &newZ );

    double convertedX, convertedY, convertedZ;
    gluUnProject(newX, newY, newZ, modelMatrix, projMatrix, viewport, &convertedX, &convertedY, &convertedZ);

    convertedX += cameraX;
    convertedY += cameraY;

//    cout << convertedX << "    " << convertedY << endl;

    xOut = (double) convertedX;
    yOut = (double) convertedY;
}

void GLScene::LoadLevelFromXML()
{
    XMLDocument xmlDoc;
    xmlDoc.LoadFile(("LevelData/" + sceneName + ".xml").c_str());

    const XMLElement* root = xmlDoc.FirstChildElement(); // gets root node

    /////////////////
    // LOAD PLATFORMS
    /////////////////

    const XMLElement* mainElements = root->FirstChildElement();
    for (const XMLElement* child = mainElements->FirstChildElement(); child != 0; child=child->NextSiblingElement())
    {
        double newWidth, newHeight, newX, newY;
        child->QueryAttribute("Width", &newWidth);
        child->QueryAttribute("Height", &newHeight);
        child->QueryAttribute("xPos", &newX);
        child->QueryAttribute("yPos", &newY);

        string newTexture = child->FirstChildElement()->GetText();

        staticObjects.push_back(new Model(newWidth, newHeight, newX, newY, "Platform", "Platform"));
        staticObjects.back()->InitModel(newTexture, true);
    }

    //////////////
    // LOAD PLAYER
    //////////////

    mainElements = mainElements->NextSiblingElement();
    double playerX, playerY;
    mainElements->QueryAttribute("xPos", &playerX);
    mainElements->QueryAttribute("yPos", &playerY);


    Player::player = new Player(playerX, playerY);
    Player::player->InitPlayer();

    ///////////////
    // LOAD TRIGGER
    ///////////////

    mainElements = mainElements->NextSiblingElement();
    double newWidth, newHeight, newX, newY;
    mainElements->QueryAttribute("Width", &newWidth);
    mainElements->QueryAttribute("Height", &newHeight);
    mainElements->QueryAttribute("xPos", &newX);
    mainElements->QueryAttribute("yPos", &newY);

    nextLevelTrigger = new Model(newWidth, newHeight, newX, newY, "LevelTrigger", "Trigger");
    nextLevelTrigger->InitModel("Images/LevelTrigger.png", true);

    //////////////////
    // LOAD BACKGROUND
    //////////////////

    mainElements = mainElements->NextSiblingElement();

    // Need to store element name into a string due to the return type being const char*
    string checkName = mainElements->Name();

    if(checkName == "Background")
    {
        // LevelCreator class has variables for background scale x and y, which is where we'll dump width and height.
        mainElements->QueryAttribute("Width", &backgroundScaleX);
        mainElements->QueryAttribute("Height", &backgroundScaleY);
        string texturePath = mainElements->FirstChildElement()->GetText();

        background = new Parallax();

        mainElements = mainElements->NextSiblingElement();
        checkName = mainElements->Name();
    }

    if(checkName == "Enemies")
    {
        for (const XMLElement* child = mainElements->FirstChildElement(); child != 0; child=child->NextSiblingElement())
        {
            double newX, newY;
            child->QueryAttribute("xPos", &newX);
            child->QueryAttribute("yPos", &newY);

            string newName, newTag;

            newName = child->FirstChildElement()->GetText(); // get the name of the enemy
            newTag = child->LastChildElement()->GetText(); // get the tag of the enemy

            if(newTag == "MeleeEnemy")
                enemies.push_back(new MeleeEnemy(newX, newY, 1.0, 1.0, newName));
            else if(newTag == "RangedEnemy")
                enemies.push_back(new RangedEnemy(newX, newY, 1.0, 1.0, newName));

            if(enemies.back())
                enemies.back()->InitEnemy();
        }
    }
}

void GLScene::ClearStaticData()
{
    for(auto& enemy : enemies)
        delete enemy;

    enemies.clear();

    for(auto& platform : staticObjects)
        delete platform;

    staticObjects.clear();

    for(auto& obj : movableObjects)
        delete obj;

    movableObjects.clear();

    delete Player::player;
    Player::player = nullptr;
}

