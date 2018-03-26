#ifndef AudioSource_H
#define AudioSource_H

#include <string>
#include <windows.h>
#include <MMSystem.h>

using namespace std;

// Handles the playback and settings of SFX and Music. ChordManager will use AudioSource to play chords
class AudioSource
{
    public:
        AudioSource();
        virtual ~AudioSource();

        // plays chord using name that's passed in as argument
        void Play(string filepath);

        // Stops playing any currently playing sound
        void Stop();

    protected:

    private:
};

#endif // AudioSource_H
