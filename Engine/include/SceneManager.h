#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <string>
#include <unordered_map>
#include <GLScene.h>

using namespace std;

// Handles Scene Loading.
class SceneManager
{
    public:
        SceneManager();
        virtual ~SceneManager();

        // Active scene can be changed by any other class and tells this class which scene to display
        static string activeScene;

        // Hashtable of scenes. Each scene must have a unique name and is hashed into the table using the name
        static unordered_map<string, GLScene*> scenes;

    protected:

    private:
};

#endif // SCENEMANAGER_H
