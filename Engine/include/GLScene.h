// updated 2/7/18

#ifndef GLSCENE_H
#define GLSCENE_H

#define _WIN32_WINNT 0x0500 // need this for controlling console window
#include <windows.h>
#include <glut.h>
//#include "freetype.h"
#include <iostream>
#include <vector>
#include <Model.h>
#include <Inputs.h>
#include <unordered_map>
#include <AudioSource.h>
#include <AudioEngine.h>
#include <Enemy.h>
#include <MeleeEnemy.h>
#include <HUD.h>
#include <RangedEnemy.h>
#include <SceneManager.h>
#include <tinyxml2.h>
#include <Particles.h>

using namespace std;
using namespace tinyxml2;

class GLScene
{
    public:
        GLScene();
        GLScene(string newName);
        virtual ~GLScene();

        // openGL rendering functions
        virtual GLint initGL();
        virtual GLint drawGLScene();
        GLvoid resizeGLScene(GLsizei, GLsizei);

        // keyboard and mouse inputs
        virtual int windowsMsg(HWND, UINT, WPARAM, LPARAM);

//        WPARAM wParam;
        float screenHeight, screenWidth;

        static vector<Model*> movableObjects; // only moving objects will check for collision
        static vector<Model*> staticObjects; // environmental, non-moving objects don't need to check for collision
        static vector<Enemy*> enemies;
        static vector<Model*> healthPacks; // vector of health pack objects in the scene

        //returns scene name
        string GetSceneName();

        // flags level loading, which will prevent rendering in the scene to avoid seg faults
        void LoadNewLevel();

        // called on by Player::TakeDamage()
        void SetGameOver();

        void GameWon();

    protected:
        unordered_map<string, AudioSource*> audioSources; // map of all environmental sounds in scene
        AudioEngine* audioEngine;
        AudioSource* BGM; // background music for this scene
        string sceneName; // keeps track of the name of the scene. Used by SceneManager
        Parallax* background; // background image for this scene
		HUD* displayHUD;
		Model* nextLevelTrigger;

        double backgroundScaleX, backgroundScaleY;

        Timer* sceneTimer;

        // Checks mouse pointer collision. Mainly used for checking mouse input on UI elements like buttons
        bool CheckPointerCollision(Model* button, double mouseX, double mouseY);

        Inputs *keyboardAndMouse;

        DeltaTime* dTime;

        // Takes mouseX and mouseY screen pixel c oordinates as input, converts them to OpenGL World coordinates, and sends them out using xOut and yOut. Pass reference parameters for xOut and yOut
        void ConvertMouseToWorld(double mouseX, double mouseY, double &xOut, double &yOut);

        // Loads player, enemy, platform, trigger data into the scene
        void LoadLevelFromXML();

    private:
        Model* gameOverWindow;
        Model* replayButton;
        Model* mainMenuButton;
        Model* pauseWindow;
        Model* resumeButton;

        bool gameOver, paused;

        void CheckGameOverCollision(WPARAM keyPressed);
        void CheckGameOverCollision(double mouseX, double mouseY);

        bool loadNewLevel; // flag for stopping the rendering of everything while new level loads.
        // Empty out the static data. Useful for loading new data
        void ClearStaticData();

        // Checks if position is overlapping specified min and max values. Used by CheckPointerCollision()
        bool Overlap(double pos, double min, double max);

        void SetPaused();
};

#endif // GLSCENE_H
