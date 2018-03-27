#include "AudioSource.h"
#include <iostream>
#include <GLScene.h>

AudioSource::AudioSource()
{
    //ctor
//    PlaySound("Audio/Music/ab9.wav", NULL, SND_ASYNC);
}

AudioSource::AudioSource(string newName, double newX, double newY, unsigned short newVolume)
{
    name = newName;
    xPos = newX;
    yPos = newY;
    lChannel = 0xFFFF;
    rChannel = 0xFFFF0000;
    SetVolume(newVolume);
}

AudioSource::~AudioSource()
{
    //dtor
}

void AudioSource::Play(string filepath)
{
    PlaySound(filepath.c_str(), NULL, SND_ASYNC);
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

    // set r/l channel balance
//    UpdatePosition();

    volume = lChannel + rChannel;

    waveOutSetVolume(NULL, volume);
}

void AudioSource::UpdatePosition()
{
    int xDist = xPos - GLScene::testPlayer->GetX();

    if(xDist > 0)
    {
        // this source is to right of player so amplify right channel and lower left channel
        DWORD newLChannel = lChannel >> xDist;

        lChannel -= newLChannel;

        std::cout << lChannel << std::endl;
//        rChannel = 0xFFFF0000 & (((newVal * 65535 - (xDist * 65535) ) / 100) * 65535);
//        lChannel = 0xFFFF & ((newVal * 65535 + (xDist * 65535)) / 100);
    }
//    else if(xDist < 0)
//    {
//        // source is to left of player so amplify left channel and lower right channel
//        lChannel = 0xFFFF & ((newVal * 65535 - (-xDist * 65535)) / 100);
//        rChannel = 0xFFFF0000 & (((newVal * 65535 + (-xDist * 65535) )/ 100) * 65535);
//    }
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
