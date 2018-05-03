#include "MainMenu.h"
#include <GLLight.h>
#include <LevelCreator.h>

MainMenu::MainMenu()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN); // get y size of screen

    sceneName = "MainMenu";

    // Add main menu to the Scene Manager
    SceneManager::scenes.insert( {"MainMenu", this} );
    SceneManager::activeScene = "MainMenu";

    // Initialize the audio engine. Will be used by other classes
    audioEngine = new AudioEngine();

    killGame = false;

    zPosButtonUI = 0;
}

MainMenu::~MainMenu()
{
    //dtor
}

GLint MainMenu::initGL()
{
    // Initialize openGL renderer for this scene

    glShadeModel(GL_SMOOTH); // Shading mode
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // set background color to black
    glClearDepth(1.0f); // depth buffer
    glEnable(GL_DEPTH_TEST); // test to see what's in front and what's in back
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL); // allows texture to have color
    GLLight Light(GL_LIGHT0);

    InitModels(); // initialize UI Elements

    return 1;
}

void MainMenu::InitModels()
{
    // instantiate UI elements
    background = new Parallax();
    startGame = new Model(2.0, 0.5, 0, 1.0, "NewGameButton", "Button");
    startGame->SetZoom(zPosButtonUI);
    exit = new Model(2.0, 0.5, 0, -1.0, "ExitButton", "Button");
    exit->SetZoom(zPosButtonUI); // set the Z position. UI elements will be at 0
    levelCreator = new Model(2.0, 0.5, 0, 0, "LevelCreatorButton", "Button");
    levelCreator->SetZoom(zPosButtonUI);

    // Bind textures for UI elements
    background->ParallaxInit("Images/Backgrounds/MenuBackground.jpg");
    startGame->InitModel("Images/UI/NewGame.png", true);
    exit->InitModel("Images/UI/Exit.png", true);
    levelCreator->InitModel("Images/UI/LevelCreator.png", true);

}

GLint MainMenu::drawGLScene()
{
    // Main loop. Render openGL elements to window every frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	gluLookAt(0, 0, 6,
            0, 0, 0,
            0.0f, 1.0f, 0.0f);

    if(killGame) // exit game
        return 0;

    glPushMatrix();
    glScaled(6.66, 6.66, 1.0); // Scale the background image
    background->DrawSquare(screenWidth, screenHeight);
    glPopMatrix();

    DrawButtons();

//    for(auto& button : maps)
//        // draw all the UI elements
//        button->DrawModel();

    return 1;
}

void MainMenu::LoadScene(string sceneName)
{
        // if we already have the level loaded, we want to delete it
        auto finder = SceneManager::scenes.find(sceneName); // find the scene in scene manager

        if(finder != SceneManager::scenes.end())
            delete SceneManager::scenes[sceneName]; // if hashtable already has map loaded, delete it

        if(sceneName == "LevelCreator")
        {
            LevelCreator* creatorScene = new LevelCreator();

            SceneManager::scenes.insert( {sceneName, creatorScene} );
            creatorScene->initGL();
        }
        else if(sceneName == "Game")
        {
            GLScene* newGame = new GLScene(sceneName); // create new map

            SceneManager::scenes.insert( {sceneName, newGame} ); // insert map into hash table
            newGame->initGL(); // initialize map
        }


        SceneManager::activeScene = sceneName; // set active scene to the new scene.

//    // Handle map loading. We pass an int so we can load a txt file that contains the same int number in the filename.
//    if(num == 0)
//        // if user selects to exit, end the game
//        killGame = true;
//    else
//    {
//        // If user selects a map, we need to load it and play it.
//
//    }
}

int MainMenu::windowsMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    if(uMsg == WM_LBUTTONDOWN)
    {
        double aspectRatio = screenWidth / screenHeight;
        double mouseX = (LOWORD(lParam) / (screenWidth / 2) - 1.0) * aspectRatio * 3.33;
        double mouseY = -(HIWORD(lParam) / (screenHeight / 2) - 1.0) / aspectRatio * 3.33;

        if(CheckPointerCollision(exit, mouseX, mouseY))
            killGame = true;
        else if(CheckPointerCollision(startGame, mouseX, mouseY))
            LoadScene("Game");
        else if(CheckPointerCollision(levelCreator, mouseX, mouseY))
            LoadScene("LevelCreator");
    }
    if(uMsg == WM_KEYDOWN)
    {
        // Handle keyboard input. User can select options 0 - 9. Hex values represent numbers 0 - 9 at top of keyboard

        const int oneKey = 0x31, twoKey = 0x32, threeKey = 0x33;

        if(wParam == oneKey || wParam == VK_NUMPAD1)
            LoadScene("Game");
        else if(wParam == twoKey || wParam == VK_NUMPAD2)
            LoadScene("LevelCreator");
        else if(wParam == threeKey || wParam == VK_NUMPAD3)
            killGame = true;

    }

	return 1;
}

void MainMenu::DrawButtons()
{
    startGame->DrawModel();
    exit->DrawModel(); // render exit button
    levelCreator->DrawModel();
}
