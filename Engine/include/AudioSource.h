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
        AudioSource(string newName, double newX, double newY, unsigned short newVolume);
        virtual ~AudioSource();

        // plays chord using name that's passed in as argument
        void Play(string filepath);

        // Stops playing any currently playing sound
        void Stop();

        // Sets the volume of this audio source
        void SetVolume(unsigned short newVal);

        // Sets l/r channel balance based on player position
        void UpdatePosition();

        // Gets the name of this AudioSource
        string GetName();

        void SetPosition(double newX, double newY);

        double GetX();
        double GetY();

    protected:

    private:
        string name;
        DWORD volume, lChannel, rChannel;
        double xPos, yPos;
};

#endif // AudioSource_H
