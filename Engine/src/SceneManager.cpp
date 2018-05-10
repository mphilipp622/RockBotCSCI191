#include "SceneManager.h"
#include <GLScene.h>
#include <LevelCreator.h>
#include <MainMenu.h>
#include <fstream>

// global static variables. Bad design but we've gone too far down this rabbit hole to come back now
unordered_map<string, GLScene*> SceneManager::scenes;
string SceneManager::activeScene;

SceneManager::SceneManager()
{
    //ctor
    activeScene = "MainMenu"; // default active scene is main menu
    scenes = {}; // initialize scenes to empty
}

SceneManager::~SceneManager()
{
    //dtor
}

GLScene* SceneManager::GetActiveScene()
{
    return scenes[activeScene];
}

void SceneManager::LoadScene(string sceneName)
{
    // check if the file exists or not.

    // if we already have the level loaded, we want to delete it
    auto finder = scenes.find(sceneName); // find the scene in scene manager

    string oldScene = activeScene;

//    if(finder != scenes.end())
//        activeScene = sceneName;

    if(sceneName == "LevelCreator")
    {
        AudioEngine::engine->stopAllSounds();
        LevelCreator* creatorScene = new LevelCreator();

        scenes.insert( {sceneName, creatorScene} );
        creatorScene->initGL();
    }
    else if(sceneName == "MainMenu")
    {
        AudioEngine::engine->stopAllSounds();
        MainMenu* newMenu = new MainMenu();

        scenes.insert( {sceneName, newMenu} );
        newMenu->initGL();
    }
    else
    {
        ifstream checkInput("LevelData/" + sceneName + ".xml");
        if(!checkInput)
            return;

        AudioEngine::engine->stopAllSounds();
        GLScene* newGame = new GLScene(sceneName); // create new map

        scenes.insert( {sceneName, newGame} ); // insert map into hash table
        newGame->initGL(); // initialize map
    }

    DeleteScene(oldScene);

    activeScene = sceneName; // set active scene to the new scene.
}

void SceneManager::LoadNextLevel()
{
    ifstream checkFile("LevelData/Level" + to_string((activeScene.back() - '0') + 1) + ".xml");

    if(!checkFile)
    {
        // if there is not a next level, then we've reached the end.
        scenes[activeScene]->GameWon();
        return;
    }


    string currentLevel = activeScene; // hold onto this so we can delete it after we initialize new level.

    // STop rendering current level
    scenes[activeScene]->LoadNewLevel();

    // Get the current level number from the back of the string. THIS WILL NOT WORK FOR LEVELS WITH TWO DIGITS LUL
    int currentLevelNumber = (activeScene.back() - '0') + 1;


    string nextLevelName = "Level" + to_string(currentLevelNumber);
    cout << nextLevelName << endl;

    // if we already have the level loaded, we want to delete it
    auto finder = scenes.find(nextLevelName); // find the scene in scene manager

    if(finder != scenes.end())
        delete scenes[nextLevelName]; // if hashtable already has level loaded, delete it


    GLScene* nextLevel = new GLScene(nextLevelName); // create new map

    scenes.insert( {nextLevelName, nextLevel} ); // insert map into hash table
    nextLevel->initGL(); // initialize map

    activeScene = nextLevelName; // set active scene to the new scene.


}

void SceneManager::ReloadLevel()
{

    GLScene* reloadedLevel = new GLScene(activeScene);

    // if we already have the level loaded, we want to delete it
    auto finder = scenes.find(activeScene); // find the scene in scene manager

    if(finder != scenes.end())
       scenes.erase(finder); // if hashtable already has level loaded, delete it

    scenes.insert( {activeScene, reloadedLevel} ); // insert map into hash table
    scenes[activeScene]->initGL(); // initialize map

}

void SceneManager::DeleteScene(string sceneName)
{
    // if we already have the level loaded, we want to delete it
    auto finder = scenes.find(sceneName); // find the scene in scene manager

    if(finder != scenes.end())
       scenes.erase(finder); // if hashtable already has level loaded, delete it

}
