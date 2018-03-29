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

void AudioSource::PlayChord(string newChord)
{
    string path = "Audio/Music/" + newChord + ".wav";
//    string path = "Audio/Music/Chords/" + chordName + ".ogg";
    AudioEngine::engine->play2D(path.c_str(), false);
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

    source->setDefaultVolume(newVal);
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
