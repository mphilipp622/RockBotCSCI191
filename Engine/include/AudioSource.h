#ifndef AudioSource_H
#define AudioSource_H

#include <string>
#include <windows.h>
#include <MMSystem.h>
#include <cmath>

using namespace std;

// Handles the playback and settings of SFX and Music. ChordManager will use AudioSource to play chords
class AudioSource
{
    public:
        AudioSource();
        AudioSource(string newName, string newFilePath, double newX, double newY, unsigned short newVolume, bool isLooping);
        virtual ~AudioSource();

        // plays chord using name that's passed in as argument
        void Play();

        // Stops playing any currently playing sound
        void Stop();

        // Sets the volume of this audio source
        void SetVolume(unsigned short newVal);

        // Sets l/r channel balance based on player position
        void UpdateChannelBalance();

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
        DWORD volume, lChannel, rChannel;
        unsigned short gain;
        double xPos, yPos;
        bool loop;
};

#endif // AudioSource_H
