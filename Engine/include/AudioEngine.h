#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <irrKlang.h>
#include <windows.h>
#include <iostream>

using namespace std;
using namespace irrklang;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

/*
Audio Engine manages all the sound in the game. There is a static instance
of the engine in this class that can be called from other classes by using
AudioEngine::engine

E.G AudioEngine::engine->play2D()

For a complete list of irrklang api, refer to
https://www.ambiera.com/irrklang/docu/index.html
*/
class AudioEngine
{
    public:
        AudioEngine();
        virtual ~AudioEngine();

        // static instance of the engine
        static ISoundEngine* engine;

        // Sets the position of the engine. Called exclusively by player to ensure the engine is always center of the screen for 3D sound to work properly.
        static void SetPosition(double newX, double newY);

    protected:

    private:
};

#endif // AUDIOENGINE_H
