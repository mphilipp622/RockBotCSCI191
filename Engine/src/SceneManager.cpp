#include "SceneManager.h"
#include <GLScene.h>
#include <LevelCreator.h>

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
    // if we already have the level loaded, we want to delete it
    auto finder = scenes.find(sceneName); // find the scene in scene manager

//    if(finder != scenes.end())
//        delete scenes[sceneName]; // if hashtable already has map loaded, delete it

    if(finder != scenes.end())
        activeScene = sceneName;
    else if(sceneName == "LevelCreator")
    {
        LevelCreator* creatorScene = new LevelCreator();

        scenes.insert( {sceneName, creatorScene} );
        creatorScene->initGL();
    }
    else
    {
        GLScene* newGame = new GLScene(sceneName); // create new map

        scenes.insert( {sceneName, newGame} ); // insert map into hash table
        newGame->initGL(); // initialize map
    }

    activeScene = sceneName; // set active scene to the new scene.
}

void SceneManager::LoadNextLevel()
{
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
