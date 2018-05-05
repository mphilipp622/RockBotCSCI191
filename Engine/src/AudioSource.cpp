#include "AudioSource.h"
#include <iostream>
#include <GLScene.h>

using namespace std;
using namespace irrklang;


AudioSource::AudioSource()
{
    // Default constructor should basically never need to be used
}

AudioSource::AudioSource(string newName, string newFilePath, double newX, double newY, float newVolume, bool isLooping)
{
    // Initializes all the private variables
    name = newName;
    filePath = newFilePath;
    xPos = newX;
    yPos = newY;
    volume = newVolume;
    loop = isLooping; // Loop is specified on creation. If loop is true, then the sound will loop when it ends
}

AudioSource::~AudioSource()
{
    //dtor
//    sound->drop();
}


//////////////////////////////////////
// SOUND PLAYBACK
//////////////////////////////////////

void AudioSource::Play()
{
    sound = AudioEngine::engine->play3D(filePath.c_str(), vec3df(xPos, yPos, 0), loop, false);
}

void AudioSource::PlayMusic()
{
    if(AudioEngine::engine->isCurrentlyPlaying(filePath.c_str()))
        return; // keep playing music if we haven't changed the song from level to level

    sound = AudioEngine::engine->play2D(filePath.c_str(), loop, true);
    sound->setVolume(volume);
    sound->setIsPaused(false);
}

void AudioSource::PlayChord(string newChord)
{

    if(sound)
    {
        // Have to pause it to drop it. Don't know why.
        sound->setIsPaused(true);
        sound->drop();
    }

    string path = "Audio/Music/Chords/" + newChord + ".ogg";
    sound = AudioEngine::engine->play2D(path.c_str(), false, true);
    sound->setIsPaused(false); // have to do this for some stupid reason.
}


/////////////////////////////////////////////
// SOUND MANIPULATION
/////////////////////////////////////////////

void AudioSource::SetVolume(float newVal)
{
    // clamp newVal to a max of 1.0 and minimum of 0
    if(newVal > 1.0)
        newVal = 1.0;
    else if(newVal < 0)
        newVal = 0;

    if(sound)
        sound->setVolume(newVal);
}


/////////////////////////////////////////////
// SOUND POSITIONING
/////////////////////////////////////////////

void AudioSource::SetPosition(double newX, double newY)
{
    xPos = newX;
    yPos = newY;
}

