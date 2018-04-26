#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <irrKlang.h>
#include <windows.h>
#include <iostream>

using namespace std;
using namespace irrklang;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

class AudioEngine
{
    public:
        AudioEngine();
        virtual ~AudioEngine();

        static ISoundEngine* engine;

        static void SetPosition(double newX, double newY);

    protected:

    private:
};

#endif // AUDIOENGINE_H
