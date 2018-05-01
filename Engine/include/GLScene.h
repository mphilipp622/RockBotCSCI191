// updated 2/7/18

#ifndef GLSCENE_H
#define GLSCENE_H

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
#include <RangedEnemy.h>
#include <SceneManager.h>

using namespace std;

class GLScene
{
    public:
        GLScene();
        virtual ~GLScene();

        // openGL rendering functions
        virtual GLint initGL();
        virtual GLint drawGLScene();
        GLvoid resizeGLScene(GLsizei, GLsizei);

        // keyboard and mouse inputs
        virtual int windowsMsg(HWND, UINT, WPARAM, LPARAM);

        // used for loading into a scene from this scene
        virtual void LoadScene(string name);

        WPARAM wParam;
        float screenHeight, screenWidth;

        static vector<Model*> movableObjects; // only moving objects will check for collision
        static vector<Model*> staticObjects; // environmental, non-moving objects don't need to check for collision
        static vector<Enemy*> enemies;
        static Inputs *keyboardAndMouse;

        //returns scene name
        string GetSceneName();

    protected:
        unordered_map<string, AudioSource*> audioSources; // map of all environmental sounds in scene
        Player* player;

        AudioSource* BGM; // background music for this scene
        string sceneName; // keeps track of the name of the scene. Used by SceneManager
        Parallax* background; // background image for this scene

        Timer* sceneTimer;

    private:
        DeltaTime* dTime;
        Enemy* testEnemy;
        Enemy* testRangedEnemy;
};

#endif // GLSCENE_H
