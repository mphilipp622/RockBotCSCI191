#ifndef AudioSource_H
#define AudioSource_H

#include <string>
#include "irrKlang.h"
#include <windows.h>
#include <AudioEngine.h>

using namespace std;

// Handles the playback and settings of SFX and Music. ChordManager will use AudioSource to play chords
class AudioSource
{
    public:
        AudioSource();
        AudioSource(string newName, string newFilePath, double newX, double newY, float newVolume, bool isLooping);
        virtual ~AudioSource();

        // Plays the sound from the filepath of the object
        void Play();

        // Plays chord of the same name that's passed to function
        void PlayChord(string chordName);

        void PlayMusic();

        // Sets the volume of this audio source
        void SetVolume(float newVal);

        // Sets the position of this audio source in openGL space
        void SetPosition(double newX, double newY);

    protected:

    private:
        string name, filePath;
        float volume;
        double xPos, yPos;
        bool loop;

        ISoundSource* source;
        ISound* sound;
        vec3df* position;
};

#endif // AudioSource_H
