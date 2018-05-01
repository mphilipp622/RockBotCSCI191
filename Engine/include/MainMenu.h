#ifndef MAINMENU_H
#define MAINMENU_H

#include <GLScene.h>
#include <Parallax.h>

// Inherits from GLScene and will be used as the main screen
class MainMenu : public GLScene
{
    public:
        MainMenu();
        virtual ~MainMenu();

        // Initialize the openGL rendering for this scene
        GLint initGL();

        // Renders this scene to the window
        GLint drawGLScene();

        // Loads scenes from this scene
        void LoadScene(int num);

        // Handles keyboard input
        int windowsMsg(HWND,UINT, WPARAM,LPARAM);

    protected:

    private:
        Model* startGame; // start game button image
        Model* howToPlay; // how to play button image
        Parallax* background; // background image for menu.
        Model* exit; // exit UI element for menu.

        // Screen width and height in pixels
        double screenWidth, screenHeight;
        bool killGame; // Used for exiting the game

        // Initializes the textures and vertices for the UI Elements in the scene
        void InitModels();

        // Audio Engine is created when main menu is loaded. Used by other classes in game
        AudioEngine* audioEngine;
};

#endif // MAINMENU_H
