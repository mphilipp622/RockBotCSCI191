#include "AudioSource.h"
#include <iostream>
#include <GLScene.h>

using namespace std;
using namespace irrklang;


AudioSource::AudioSource()
{
    //ctor
//    PlaySound("Audio/Music/ab9.wav", NULL, SND_ASYNC);
}

AudioSource::AudioSource(string newName, string newFilePath, double newX, double newY, float newVolume, bool isLooping)
{
    name = newName;
    filePath = newFilePath;
    xPos = newX;
    yPos = newY;
    volume = newVolume;
    loop = isLooping;

    sound = 0;
    source = 0;
}

AudioSource::~AudioSource()
{
    //dtor
    sound->drop();
}

void AudioSource::Update(double newX, double newY)
{
}

void AudioSource::Play()
{
    sound = AudioEngine::engine->play3D(filePath.c_str(), vec3df(xPos, yPos, 0), loop, false);
}

void AudioSource::PlayMusic()
{
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

void AudioSource::Stop()
{
    sound->stop();
}

void AudioSource::SetVolume(float newVal)
{
    // clamp newVal to a max of 1.0 and minimum of 0
    if(newVal > 1.0)
        newVal = 1.0;
    else if(newVal < 0)
        newVal = 0;

    if(sound)
        sound->setVolume(newVal);
//    source->setDefaultVolume(newVal);
}

string AudioSource::GetName()
{
    return name;
}

void AudioSource::SetPosition(double newX, double newY)
{
    xPos = newX;
    yPos = newY;
}

double AudioSource::GetX()
{
    return xPos;
}

double AudioSource::GetY()
{
    return yPos;
}
