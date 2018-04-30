#include "SceneManager.h"

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
