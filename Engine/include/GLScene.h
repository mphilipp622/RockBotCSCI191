// updated 2/7/18

#ifndef GLSCENE_H
#define GLSCENE_H

#define _WIN32_WINNT 0x0500 // need this for controlling console window
#include <windows.h>
#include <glut.h>
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

        // used for loading into a scene from this scene
        virtual void LoadScene(string name);

//        WPARAM wParam;
        float screenHeight, screenWidth;

        static vector<Model*> movableObjects; // only moving objects will check for collision
        static vector<Model*> staticObjects; // environmental, non-moving objects don't need to check for collision
        static vector<Enemy*> enemies;

        //returns scene name
        string GetSceneName();

    protected:
        unordered_map<string, AudioSource*> audioSources; // map of all environmental sounds in scene
        AudioEngine* audioEngine;
        AudioSource* BGM; // background music for this scene
        string sceneName; // keeps track of the name of the scene. Used by SceneManager
        Parallax* background; // background image for this scene
		HUD* displayHUD;

        double backgroundScaleX, backgroundScaleY;

        Timer* sceneTimer;

        // Checks mouse pointer collision. Mainly used for checking mouse input on UI elements like buttons
        bool CheckPointerCollision(Model* button, double mouseX, double mouseY);

        // called in GLscene and children classes to clear out staticObjects, movableObjects, and enemies
        void CleanStaticData();

        Inputs *keyboardAndMouse;

        DeltaTime* dTime;

        // Takes mouseX and mouseY screen pixel c oordinates as input, converts them to OpenGL World coordinates, and sends them out using xOut and yOut. Pass reference parameters for xOut and yOut
        void ConvertMouseToWorld(double mouseX, double mouseY, double cameraX, double cameraY, double &xOut, double &yOut);

        // Loads player, enemy, platform, trigger data into the scene
        void LoadLevelFromXML();

    private:

        Enemy* testEnemy;
        Enemy* testRangedEnemy;
        Model* nextLevelTrigger;

        // Empty out the static data. Useful for loading new data
        void ClearStaticData();

        // Checks if position is overlapping specified min and max values. Used by CheckPointerCollision()
        bool Overlap(double pos, double min, double max);
};

#endif // GLSCENE_H
