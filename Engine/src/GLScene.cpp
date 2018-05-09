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
    ClearStaticData();
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    sceneName = "Game";
}

GLScene::GLScene(string newName)
{
    ClearStaticData();
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    sceneName = newName;
    gameOver = false;
}


GLScene::~GLScene()
{
}

// Static Variables for use in player class to check collision
vector<Model*> GLScene::movableObjects;
vector<Model*> GLScene::staticObjects;
vector<Enemy*> GLScene::enemies;
vector<Model*> GLScene::healthPacks;

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

    nextLevelTrigger = nullptr;
    gameOverWindow = nullptr;
    replayButton = nullptr;
    mainMenuButton = nullptr;
    background = nullptr;

    loadNewLevel = true;
    LoadLevelFromXML();

    displayHUD = new HUD();
    keyboardAndMouse = new Inputs();
    sceneTimer = new Timer();

    sceneTimer->Start();

    BGM = new AudioSource("Music", "Audio/Music/BGM/DrumLoop.wav",0, 0, .6, true);
    BGM->PlayMusic();
    dTime = new DeltaTime();
    loadNewLevel = false;

    return true;
}

GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if(Player::player->IsDead())
        SetGameOver();

//    if(loadNewLevel)
//        return 1; // stop rendering the scene while next level loads.

    gluLookAt(Player::player->GetX(), Player::player->GetY(), 6.0,
            Player::player->GetX(), Player::player->GetY(), Player::player->GetZoom(),
            0.0f, 1.0f, 0.0f);

    if(gameOver)
    {
        gameOverWindow->DrawModel();
        replayButton->DrawModel();
        mainMenuButton->DrawModel();
        return 1;
    }

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glScaled(backgroundScaleX, backgroundScaleY, 1);
    background->DrawSquare(screenWidth, screenHeight); // draw background
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    displayHUD->showHP(Player::player);
    glDisable(GL_TEXTURE_2D);

    for(auto& model : movableObjects)
    {
        glEnable(GL_TEXTURE_2D);
        model->Update();
        glDisable(GL_TEXTURE_2D);
    }


    for(auto& model : staticObjects)
    {
        glEnable(GL_TEXTURE_2D);
        model->DrawModel();
        glDisable(GL_TEXTURE_2D);
    }


    for(auto& healthPack : healthPacks)
    {
        glEnable(GL_TEXTURE_2D);
        healthPack->DrawModel();
        glDisable(GL_TEXTURE_2D);
    }

    for(auto& enemy : enemies)
    {
        glEnable(GL_TEXTURE_2D);
        enemy->Update();
        glDisable(GL_TEXTURE_2D);
    }


    if(Player::player)
    {
        glEnable(GL_TEXTURE_2D);
        Player::player->Update();
        glDisable(GL_TEXTURE_2D);
    }

    if(nextLevelTrigger)
    {
        glEnable(GL_TEXTURE_2D);
        nextLevelTrigger->DrawModel();
        glDisable(GL_TEXTURE_2D);
        if(nextLevelTrigger->LevelTriggerCollision())
        {
            loadNewLevel = true;
            SceneManager::LoadNextLevel();
            delete this;
        }

    }

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
        if(gameOver)
        {
            // Check for game over menu inputs
            CheckGameOverCollision(wParam);
            return 1;
        }

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
        if(gameOver)
        {
            // Check for gameover menu inputs
            CheckGameOverCollision(LOWORD(lParam), HIWORD(lParam));
            return 1;
        }

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

void GLScene::ConvertMouseToWorld(double mouseX, double mouseY, double &xOut, double &yOut)
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

//    convertedX += cameraX;
//    convertedY += cameraY;

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

    string nextLevelTexture = mainElements->LastChildElement()->GetText();

    nextLevelTrigger = new Model(newWidth, newHeight, newX, newY, "NextLevel", "LevelTrigger");
    nextLevelTrigger->InitModel(nextLevelTexture, true);

    /////////////////////
    // LOAD TEXT TRIGGERS
    /////////////////////

    mainElements = mainElements->NextSiblingElement();

    // Need to store element name into a string due to the return type being const char*
    string checkName = mainElements->Name();

    if(checkName == "TextTriggers")
    {
        for (const XMLElement* child = mainElements->FirstChildElement(); child != 0; child=child->NextSiblingElement())
        {
            double newX, newY, newWidth, newHeight;
            child->QueryAttribute("xPos", &newX);
            child->QueryAttribute("yPos", &newY);
            child->QueryAttribute("Width", &newWidth);
            child->QueryAttribute("Height", &newHeight);

            string newText;

            if(child->FirstChildElement())
                newText = child->FirstChildElement()->GetText(); // get the name of the enemy

            Player::player->AddTextTrigger(new Trigger(newX, newY, newWidth, newHeight, newText, "TextTrigger"));
        }

        mainElements = mainElements->NextSiblingElement();
        checkName = mainElements->Name();
    }

    ////////////////////
    // LOAD HEALTH PACKS
    ////////////////////

    if(checkName == "HealthPacks")
    {
        for (const XMLElement* child = mainElements->FirstChildElement(); child != 0; child=child->NextSiblingElement())
        {
            double newX, newY, newWidth, newHeight;
            child->QueryAttribute("xPos", &newX);
            child->QueryAttribute("yPos", &newY);
            child->QueryAttribute("Width", &newWidth);
            child->QueryAttribute("Height", &newHeight);

            healthPacks.push_back(new Model(newWidth, newHeight, newX, newY, "HealthPack", "HealthPack"));

            healthPacks.back()->InitModel("Images/Misc/HealthPack.png", true);
        }

        mainElements = mainElements->NextSiblingElement();
        checkName = mainElements->Name();
    }

    //////////////////
    // LOAD BACKGROUND
    //////////////////
    if(checkName == "Background")
    {
        // LevelCreator class has variables for background scale x and y, which is where we'll dump width and height.
        mainElements->QueryAttribute("Width", &backgroundScaleX);
        mainElements->QueryAttribute("Height", &backgroundScaleY);
        string texturePath = mainElements->FirstChildElement()->GetText();

        cout << texturePath << endl;
        background = new Parallax();
        background->ParallaxInit(texturePath);

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
//    delete dTime;
    for(auto& enemy : enemies)
        delete enemy;

    enemies.clear();

    for(auto& platform : staticObjects)
        delete platform;

    staticObjects.clear();

    for(auto& obj : movableObjects)
        delete obj;

    movableObjects.clear();

    for(auto& healthPack : healthPacks)
        delete healthPack;

    healthPacks.clear();

    delete Player::player;
    Player::player = nullptr;
}

void GLScene::LoadNewLevel()
{
    loadNewLevel = true;
}

void GLScene::SetGameOver()
{
    // Create menu graphics for game over menu if they don't already exist
    gameOverWindow = new Model(1.5, 1.5, Player::player->GetX(), Player::player->GetY(), "GameOverMenu", "UI");
    replayButton = new Model(1.0, 0.3, gameOverWindow->GetX(), gameOverWindow->GetY() + 0.1, "ReplayButton", "UI");
    mainMenuButton = new Model(1.0, 0.3, gameOverWindow->GetX(), gameOverWindow->GetY() - 0.3, "MainMenuButton", "UI");

    gameOverWindow->InitModel("Images/UI/GameOverMenu.png", true);
    replayButton->InitModel("Images/UI/Restart.png", true);
    mainMenuButton->InitModel("Images/UI/MainMenu.png", true);

    gameOver = true;
}

void GLScene::CheckGameOverCollision(WPARAM keyPressed)
{
    if(keyPressed == 0x31 || keyPressed == VK_NUMPAD1) // 1 key on keyboard
    {
        loadNewLevel = true;
        SceneManager::ReloadLevel();
        delete this;
    }
    else if(keyPressed == 0x32 || keyPressed == VK_NUMPAD2)
    {
        loadNewLevel = true;
        AudioEngine::engine->stopAllSounds();
        SceneManager::LoadScene("MainMenu");
        SceneManager::DeleteScene(sceneName);
        delete this;
    }
}

void GLScene::CheckGameOverCollision(double mouseX, double mouseY)
{
    // Mouse pointer selection of game over menu.

    double convertedX, convertedY;
    ConvertMouseToWorld(mouseX, mouseY, convertedX, convertedY);

    if(CheckPointerCollision(replayButton, convertedX, convertedY))
    {
        loadNewLevel = true;
        SceneManager::ReloadLevel();
        delete this;
    }
    else if(CheckPointerCollision(mainMenuButton, convertedX, convertedY))
    {
        loadNewLevel = true;
        SceneManager::LoadScene("MainMenu");
        AudioEngine::engine->stopAllSounds();
        SceneManager::DeleteScene(sceneName);
        delete this;
    }
}

