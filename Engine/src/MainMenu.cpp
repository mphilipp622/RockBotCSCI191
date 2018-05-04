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

int MainMenu::windowsMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    if(uMsg == WM_LBUTTONDOWN)
    {
        double mouseX, mouseY;

        ConvertMouseToWorld(LOWORD(lParam), HIWORD(lParam), mouseX, mouseY);

        if(CheckPointerCollision(exit, mouseX, mouseY))
            killGame = true;
        else if(CheckPointerCollision(startGame, mouseX, mouseY))
            SceneManager::LoadScene("Level1");
        else if(CheckPointerCollision(levelCreator, mouseX, mouseY))
            SceneManager::LoadScene("LevelCreator");
    }
    if(uMsg == WM_KEYDOWN)
    {
        // Handle keyboard input. User can select options 0 - 9. Hex values represent numbers 0 - 9 at top of keyboard

        const int oneKey = 0x31, twoKey = 0x32, threeKey = 0x33;

        if(wParam == oneKey || wParam == VK_NUMPAD1)
            SceneManager::LoadScene("Level1");
        else if(wParam == twoKey || wParam == VK_NUMPAD2)
            SceneManager::LoadScene("LevelCreator");
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
