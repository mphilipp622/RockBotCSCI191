#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <string>
#include <unordered_map>

using namespace std;

class GLScene; // forward declaration of GLScene. This is due to header files being included at wrong times.

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

        static GLScene* GetActiveScene();

        // Loads a scene by name using sceneName parameter
        static void LoadScene(string sceneName);

        // Called by Player::CheckTriggerCollision(). Will load the next level from the current level.
        static void LoadNextLevel();

    protected:

    private:
};

#endif // SCENEMANAGER_H
