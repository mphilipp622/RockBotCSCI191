#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include <GLScene.h>
#include <iostream>
#include <Trigger.h>

/*
DOCUMENTATION
----------------------------------------
OBJECT CREATION
----------------------------------------
B = Create Background. When asked for filename, put in the name of the file + the extension
M = create a platform / Model. When asked for filename, put in the name of the file + the extension
P = create player.
L = Create Next Level Trigger
T = Create Text Trigger. NOTE: Text Triggers will not visibly show in game. They only show in level creator for your reference
E = Create an enemy. You'll be asked the kind of enemy to create. Read the on screen menu for instructions
H = Create health pack.

----------------------------------------
LOADING / SAVING
----------------------------------------
ENTER = Save Map. When asked for an input, use 0 - 9 to specify which level you are saving. (Level 1, 2, 3, etc.) ONLY put in the integer number, such as 1, 2, 3.
Right Shift = Load Map. When asked for an input, use 0 - 9 to specify which level to load.

NOTE: Levels in-game will be loaded sequentially. When you click "New Game", level 1 is loaded. If you touch the next level trigger in level 1,
level 2 will be loaded, etc.

I may work up a level selection menu for easier testing

----------------------------------------
OBJECT MANIPULATION
----------------------------------------
+ / - = Scale Width of selected object up and down
up arrow / down arrow = Scale height of selected object up and down.
Left Click on an object = select the object.
HOLD left click while an object is selected to move it around.
Right click = deselect object
DELETE = While an object is selected (highlighted in red), press delete to delete it

----------------------------------------
CAMERA OPTIONS
----------------------------------------
WASD = Move camera around in the scene
Mouse Wheel = Zoom in and out

----------------------------------------
XML FILE INFO
----------------------------------------
XML Files are saved into the project folder/LevelData. If you want to backup a level design for any reason, I recommend saving the xml file into a
separate location for later use.

----------------------------------------
FILE PATH INFO
----------------------------------------
List of relative file paths for platforms, backgrounds, and level triggers. If you wish to download files from the internet and utilize them for textures,
you'll want to save the files to these file paths to ensure they can be loaded and saved in the level creator properly.

The below file paths are relative to your project location.

Platforms = Images/Platforms
Backgrounds = Images/Backgrounds
NextLevelTrigger = Images/Misc

----------------------------------------
BUGS
----------------------------------------
The main bug I am aware of is when being asked for filename inputs, sometimes the console window will automatically read a \n character.
I think this is due to the cin buffer not being cleared out before user is asked for input.

If you want to try and fix this bug, feel free. Typically, when this issue happens, I will delete the new object and remake it.

*/

class LevelCreator : public GLScene
{
    public:
        LevelCreator();
        virtual ~LevelCreator();

        // Initialize the openGL rendering for this scene
        GLint initGL();

        // Renders this scene to the window
        GLint drawGLScene();

        // Loads scenes from this scene
        void LoadScene(string sceneName);

        // Handles keyboard input
        int windowsMsg(HWND,UINT, WPARAM,LPARAM);

    protected:

    private:
        bool killGame;
        string playerTexturePath;

        // used for minimizing and restoring the console window when input is needed
        HWND consoleWindow;

        bool mouseDown; // tracks if mouse is held down.

        vector<Model*> platforms;
        vector<Model*> enemies; // enemies will be models since we only need x, y positions
        Model* player; // Player only needs to be a model for the level creator. We'll grab the positions for the actual game scene
//        Parallax* background; // background image for menu.
        Model* selectedModel; // user selects this with the mouse and can then manipulate the model
        vector<Model*> triggers;
        vector<Model*> healthPacks;

        string backgroundTexture;

        // will be used for moving the camera around the scene
        double cameraPosX, cameraPosY, cameraPosZ, cameraSpeed, cameraMoveIncrement;

        // these strings represent the relative file paths to the folders containing their textures
        string backgroundRelativeFilePath, platformRelativeFilePath, playerRelativeFilePath, enemyRelativeFilePath;

        // Screen width and height in pixels
        double screenWidth, screenHeight;

        // flag to lock user input while waiting for input from console
        bool waitingForConsoleInput;

        // Initializes the textures and vertices for the UI Elements in the scene
        void InitModels();

        float zPosButtonUI; // used for setting z position of all UI Button elements

        // draws UI buttons
        void DrawButtons();


        ///////////////////////////////
        // OBJECT CREATION/DELETION
        ///////////////////////////////

        // Gets filename from input and instantiates a background model
        void CreateBackground();

        // Parses filename from input and instantiates a new platform model
        void CreatePlatform();

        // Moves platform to the position the user clicked on screen
        void MoveObject(double mouseX, double mouseY);

        // Places player
        void CreatePlayer();

        // Places an enemy
        void CreateEnemy();

        // Places a level trigger in the scene
        void CreateLevelTrigger();

        // Places a text trigger in the scene
        void CreateTextTrigger();

        // Places a Health Pack in the scene
        void CreateHealthPack();

        // Deletes the selectedObject from the scene
        void DeleteObject();



        //////////////////////
        // OBJECT MODIFICATION
        //////////////////////

        // Modifies the scale of the currently selected model in the scene. Passing a negative value to either parameter will decrease the associated scale. Passing a positive value will increase the associated scale.
        void ModifyModelDimensions(double widthScale, double heightScale);

        // Moves the camera position.
        void MoveCamera(double xMove, double yMove);

        // Checks pointer collision against a model and selects it if collision happens
        void SelectModel(double mouseX, double mouseY);

        void EditTextTrigger();

        /////////////////////
        // HELPER FUNCTIONS
        /////////////////////

        // Brings console window to front and activates it for user input
        void ShowConsoleWindow();

        // Sets colors on previous selected model and new selected model and updates the selectedModel pointer.
        void SetSelectedModel(Model* newModel);

        // gets filename from user input. relativePath will be passed by the CreateBackground, CreatePlatform, etc. functions
        string GetFilenameFromInput();

        // Cleans out all pointers and data structures
        void ClearScene();

        // Zooms camera in and out
        void ZoomCamera(int delta);

        //////////////////////
        // XML SAVING/LOADING
        //////////////////////

        // Saves all the model positions in the scene into an xml document
        void SaveLevelToXML();

        // Loads Level for editing
        void LoadLevelFromXML();
};


#endif // LEVELCREATOR_H
