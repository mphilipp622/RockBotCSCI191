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

        // Stops playing any currently playing sound
        void Stop();

        // Sets the volume of this audio source
        void SetVolume(float newVal);

        // Gets the name of this AudioSource
        string GetName();

        void SetPosition(double newX, double newY);

        double GetX();
        double GetY();

        // called by drawGLScene in GLScene classes.
        void Update(double newX, double newY);

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
