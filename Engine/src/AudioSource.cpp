#include "AudioSource.h"
#include <iostream>
#include <GLScene.h>

using namespace std;

AudioSource::AudioSource()
{
    //ctor
//    PlaySound("Audio/Music/ab9.wav", NULL, SND_ASYNC);
}

AudioSource::AudioSource(string newName, string newFilePath, double newX, double newY, unsigned short newVolume, bool isLooping)
{
    name = newName;
    filePath = newFilePath;
    xPos = newX;
    yPos = newY;
    lChannel = 0xFFFF;
    rChannel = 0xFFFF0000;
    loop = isLooping;
    SetVolume(newVolume);
}

AudioSource::~AudioSource()
{
    //dtor
}

void AudioSource::Update(double newX, double newY)
{
    SetPosition(newX, newY); // update x, y coordinates for the source. Only relevant for movable objects
    UpdateChannelBalance(); // set L/R channel balance
}

void AudioSource::Play()
{
    if(loop)
        PlaySound(filePath.c_str(), NULL, SND_ASYNC | SND_LOOP);
    else
        PlaySound(filePath.c_str(), NULL, SND_ASYNC);
}

void AudioSource::Stop()
{
    PlaySound(NULL, NULL, SND_ASYNC);
}

void AudioSource::SetVolume(unsigned short newVal)
{
    if(newVal > 100)
        newVal = 100; // clamp newVal to a max of 100

    // figure out the hex value of the new volume and scale it from 0 to 100.
    lChannel = 0xFFFF & (newVal * 65535 / 100);
    rChannel = 0xFFFF0000 & ((newVal * 65535 / 100) * 65535);
    gain = newVal;

    volume = lChannel + rChannel;

    waveOutSetVolume(NULL, volume);
}

void AudioSource::UpdateChannelBalance()
{
    double xDist = xPos - Player::player->GetX();

    if(xDist > 0)
    {
        // this source is to right of player so keep right channel the same and lower left channel
        if(gain - (abs(xDist) * 20) > 0)
            lChannel = 0xFFFF & (int)((gain - (abs(xDist) * 20)) * 65535 / 100);
        else
            lChannel = 0;
    }
    else if(xDist < 0)
    {
        // this source is to left of player so keep left channel the same and lower right channel
        if(gain - (abs(xDist) * 20) > 0)
            rChannel = 0xFFFF0000 & ((int)((gain - (abs(xDist) * 20)) * 65535 / 100) * 65535);
        else
            rChannel = 0;
    }

    volume = lChannel + rChannel;

    waveOutSetVolume(NULL, volume);
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
