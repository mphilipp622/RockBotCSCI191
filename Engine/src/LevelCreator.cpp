#include "LevelCreator.h"

#include <GLLight.h>

LevelCreator::LevelCreator()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    sceneName = "LevelCreator";

    // Add main menu to the Scene Manager
    SceneManager::scenes.insert( {"LevelCreator", this} );
    SceneManager::activeScene = "LevelCreator";

    zPosButtonUI = 0;
    killGame = false;

    backgroundRelativeFilePath = "Images/Backgrounds/";
    platformRelativeFilePath = "Images/Platforms/";
    playerRelativeFilePath = "Images/Player/";
    enemyRelativeFilePath = "Images/Enemies/";

    waitingForConsoleInput = false;
    mouseDown = false;
    mouseMoveSpeed = 10.0;
    mouseIncrement = 0.5;

    prevMouseX = 0;
    prevMouseY = 0;

    backgroundScaleX = 12.0;
    backgroundScaleY = 12.0;

    cameraPosX = 0;
    cameraPosY = 0;
    cameraSpeed = 100.0;
    cameraMoveIncrement = 0.4; // this is the base unit that the camera will move when user presses WASD

    consoleWindow = GetConsoleWindow();
}

LevelCreator::~LevelCreator()
{
    //dtor
}

GLint LevelCreator::initGL()
{

    glShadeModel(GL_SMOOTH); // Shading mode
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // set background color to black
    glClearDepth(1.0f); // depth buffer
    glEnable(GL_DEPTH_TEST); // test to see what's in front and what's in back
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL); // allows texture to have color
    GLLight Light(GL_LIGHT0);

    dTime = new DeltaTime();
}

void LevelCreator::InitModels()
{

}

void LevelCreator::DrawButtons()
{

}

GLint LevelCreator::drawGLScene()
{
    // Main loop. Render openGL elements to window every frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	gluLookAt(cameraPosX, cameraPosY, 6,
            cameraPosX, cameraPosY, 0,
            0.0f, 1.0f, 0.0f);

    if(killGame) // exit game
        return 0;

    if(background)
    {
        glPushMatrix();
        glScaled(backgroundScaleX, backgroundScaleY, 1.0); // Scale the background image
        background->DrawSquare(screenWidth, screenHeight);
        glPopMatrix();
    }

    for(auto& platform : platforms)
        platform->DrawModel();

    for(auto& enemy : enemies)
        enemy->DrawModel();

    if(player)
        player->DrawModel();

    dTime->UpdateDeltaTime();

    return 1;
}

void LevelCreator::LoadScene(string sceneName)
{


}

int LevelCreator::windowsMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    const int bKey = 0x42, wKey = 0x57, sKey = 0x53, aKey = 0x41, dKey = 0x44, mKey = 0x4D, pKey = 0x50, eKey = 0x45;

    if(uMsg == WM_KEYDOWN)
    {
        if(waitingForConsoleInput)
            return 1; // prevent input while we're waiting for console input


        ////////////////////////
        //  BACKGROUND CREATION
        ////////////////////////
        if(wParam == bKey)
        {
            ShowConsoleWindow(); // pop up the console window for input.

            CreateBackground();

            SetForegroundWindow(hWnd); // set the game window back to front
        }


        ////////////////////////////////
        // Model Dimension Modification
        ////////////////////////////////

        else if(wParam == VK_ADD)
            // '+' key will increase model's x scale
            ModifyModelDimensions(1.0, 0);
        else if(wParam == VK_SUBTRACT)
            // '-' key will decrease model's x scale
            ModifyModelDimensions(-1.0, 0);
        else if(wParam == VK_UP)
            // Up Arrow Key will increase model's Y scale
            ModifyModelDimensions(0, 1.0);
        else if(wParam == VK_DOWN)
            // Down Arrow key will decrease model's Y scale
            ModifyModelDimensions(0, -1.0);


        ////////////////////
        //  CAMERA MOVEMENT
        ////////////////////

        else if(wParam == wKey)
            // Move camera up
            MoveCamera(0, 1.0);
        else if(wParam == sKey)
            // Move camera down
            MoveCamera(0, -1.0);
        else if(wParam == aKey)
            // Move camera left
            MoveCamera(-1.0, 0);
        else if(wParam == dKey)
            // Move camera right
            MoveCamera(1.0, 0);


        ////////////////////
        // PLATFORM CREATION
        ////////////////////
        else if(wParam == mKey)
        {
            ShowConsoleWindow();

            CreatePlatform();

            SetForegroundWindow(hWnd); // set the game window back to front
        }


        //////////////////
        // PLAYER CREATION
        //////////////////
        else if(wParam == pKey && !player)
            CreatePlayer(); // if player doesn't exist, create him


        /////////////////
        // ENEMY CREATION
        /////////////////
        else if(wParam == eKey)
        {
            ShowConsoleWindow();

            CreateEnemy();

            SetForegroundWindow(hWnd); // set the game window back to front
        }


        //////////////////////////////////
        // DESELECT MODEL OR BRING UP MENU
//        //////////////////////////////////
//        else if(wParam == VK_ESCAPE)
//        {
//            // If user presses escape and a model is selected, de-select it
//            if(selectedModel)
//                SetSelectedModel(nullptr);
////            else
////                // otherwise, bring up menu
////                LoadMenu();
//        }
    }


    //////////////////////////////////////
    //   MODEL SELECTION WITH RIGHT MOUSE
    //////////////////////////////////////

    if(uMsg == WM_RBUTTONDOWN)
    {
        double aspectRatio = screenWidth / screenHeight;
        double mouseX = (LOWORD(lParam) / (screenWidth / 2) - 1.0) * aspectRatio * 3.33;
        double mouseY = -(HIWORD(lParam) / (screenHeight / 2) - 1.0) / aspectRatio * 3.33;

        SelectModel(mouseX, mouseY);
    }


    ////////////////////////////////////
    //  MODEL MOVEMENT WITH LEFT MOUSE
    ////////////////////////////////////

    if(uMsg == WM_LBUTTONDOWN || mouseDown)
    {
        mouseDown = true;
    }

    if(uMsg == WM_LBUTTONUP)
        mouseDown = false;

    if(uMsg == WM_MOUSEMOVE && mouseDown)
    {
        // Allows user to move the selectedModel by clicking and dragging in the scene
        double aspectRatio = screenWidth / screenHeight;
        double mouseX = (LOWORD(lParam) / (screenWidth / 2) - 1.0) * aspectRatio * 3.33;
        double mouseY = -(HIWORD(lParam) / (screenHeight / 2) - 1.0) / aspectRatio * 3.33;

        MoveObject(mouseX, mouseY);
        prevMouseX = mouseX;
        prevMouseY = mouseY;
    }
}

void LevelCreator::CreateBackground()
{
    waitingForConsoleInput = true; // lock further input until we're done

    // get filename input first
    cout << "Making Background..." << endl;

    if(!background)
        background = new Parallax();

    string filename = GetFilenameFromInput();
    background->ParallaxInit(backgroundRelativeFilePath + filename);

    waitingForConsoleInput = false; // unlock input
}

void LevelCreator::CreatePlatform()
{
    waitingForConsoleInput = true;

    cout << "Making Platform..." << endl;

    string filepath = platformRelativeFilePath + GetFilenameFromInput();

    // instantiate model with default Width and Height of 1 and spawned at camera's center
    Model* temp = new Model(1.0, 1.0, cameraPosX, cameraPosY, "Platform" + to_string(platforms.size()), "Platform");
    temp->InitModel(filepath, true);

    platforms.push_back(temp);

    SetSelectedModel(platforms.back());

    waitingForConsoleInput = false;
}

void LevelCreator::CreatePlayer()
{
    cout << "Making Player..." << endl;

    player = new Model(1.0, 1.0, cameraPosX, cameraPosY, "Player", "Player"); // spawn player in middle of screen
    player->InitModel("Images/Player/Test_Idle_0000.png", true);

    SetSelectedModel(player);
}

void LevelCreator::CreateEnemy()
{
    waitingForConsoleInput = true;

    cout << "Making Enemy..." << endl;
    cout << "Choose The Type of Enemy To Make\n\t1 = Melee Enemy\n\t2 = Ranged Enemy" << endl;

    char type;
    cin >> type;

    type = type - '0'; // convert to integer from ascii

    string filepath;
    Model* temp;

    // Enemy tags will be used in the XML file to determine which class to spawn
    if(type == 1)
    {
        filepath = enemyRelativeFilePath + "MeleeIdle.png";
        temp = new Model(1.0, 1.0, cameraPosX, cameraPosY, "Enemy" + to_string(enemies.size()), "MeleeEnemy");
    }
    else if(type == 2)
    {
        filepath = enemyRelativeFilePath + "RangedIdle0.png";
        temp = new Model(1.0, 1.0, cameraPosX, cameraPosY, "Enemy" + to_string(enemies.size()), "RangedEnemy");
    }

    // instantiate model with default Width and Height of 1 and spawned at camera's center
    temp->InitModel(filepath, true);

    enemies.push_back(temp);

    SetSelectedModel(enemies.back()); // set new selected model

    waitingForConsoleInput = false;
}

string LevelCreator::GetFilenameFromInput()
{
    string path;

    cout << "Input texture file name (don't input full path): ";
    getline(cin, path);

    return path;
}

void LevelCreator::ModifyModelDimensions(double widthScale, double heightScale)
{
    // When user presses + or -, they can modify the width of the model they have currently selected.
    // When user presses up or down arrow, they can modify the height of the model they have selected.
    // If the user has no model selected and they press any of these keys, then they will modify the scale for the background

    if(!selectedModel)
    {
        // If no model is selected, then we assume the background is selected and scale it
        backgroundScaleX += 0.1 * widthScale; // if scale is - then this will subtract. Otherwise it will add
        backgroundScaleY += 0.1 * heightScale;
    }
    else if(selectedModel == player || selectedModel->GetTag() == "MeleeEnemy" || selectedModel->GetTag() == "RangedEnemy")
        return; // don't allow user to modify the dimensions of the player or enemies
    else
    {
        double newWidth = selectedModel->GetWidth() + (0.1 * widthScale);
        double newHeight = selectedModel->GetHeight() + (0.1 * heightScale);

        selectedModel->SetWidth(newWidth);
        selectedModel->SetHeight(newHeight);
    }
}

void LevelCreator::MoveCamera(double xMove, double yMove)
{
    // Pass 0 for xMove or yMove to keep that axis from being moved
    // Pass + 1 for xMove or yMove to increase the position of the axis.
    // Pass -1 for xMove or yMove to decrease the position of the axis.

    cameraPosX += cameraMoveIncrement * xMove * cameraSpeed * dTime->GetDeltaTime();
    cameraPosY += cameraMoveIncrement * yMove * cameraSpeed * dTime->GetDeltaTime();
}

void LevelCreator::MoveObject(double mouseX, double mouseY)
{
    if(!selectedModel)
        return; // if no model is selected, leave the function

    double xDir = mouseX - prevMouseX;
    double yDir = mouseY - prevMouseY;

    // initialize final values to the current X and Y values in case we don't move anywhere on the mouse
    double finalX = selectedModel->GetX();
    double finalY = selectedModel->GetY();

    if(xDir > 0)
        finalX = selectedModel->GetX() + (mouseIncrement * mouseMoveSpeed * dTime->GetDeltaTime());
    else if(xDir < 0)
        finalX = selectedModel->GetX() - (mouseIncrement * mouseMoveSpeed * dTime->GetDeltaTime());

    if(yDir > 0)
        finalY = selectedModel->GetY() + (mouseIncrement * mouseMoveSpeed * dTime->GetDeltaTime());
    else if(yDir < 0)
        finalY = selectedModel->GetY() - (mouseIncrement * mouseMoveSpeed * dTime->GetDeltaTime());

    selectedModel->SetPosition(finalX, finalY);
}

void LevelCreator::ShowConsoleWindow()
{
    ShowWindow(consoleWindow, SW_RESTORE);
    SetForegroundWindow(consoleWindow);
}

void LevelCreator::SetSelectedModel(Model* newModel)
{
    if(selectedModel)
        selectedModel->SetColor(1.0, 1.0, 1.0); // if selected model exists, set its color back to normal

    selectedModel = newModel;

    if(selectedModel)
        selectedModel->SetColor(1.0, 0, 0);
}

void LevelCreator::SelectModel(double mouseX, double mouseY)
{
    // Alter mouse x and y so it is relative to the camera's position in the scene
    mouseX += cameraPosX;
    mouseY += cameraPosY;

    // This will deselect the selectedModel. Allowing user to right-click empty space to deselect.
    SetSelectedModel(nullptr);

    // Iterate through all the models in the scene and check for mouse pointer collision.
    for(auto& platform : platforms)
    {
        if(CheckPointerCollision(platform, mouseX, mouseY))
        {
            // Set the new selected model
            SetSelectedModel(platform);
            return;
        }
    }

    for(auto& enemy : enemies)
    {
        if(CheckPointerCollision(enemy, mouseX, mouseY))
        {
            // Set the new selected model
            SetSelectedModel(enemy);
            return;
        }
    }

    if(player)
    {
        if(CheckPointerCollision(player, mouseX, mouseY))
            SetSelectedModel(player);
    }

}
