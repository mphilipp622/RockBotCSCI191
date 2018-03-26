#include "AudioSource.h"

AudioSource::AudioSource()
{
    //ctor
//    PlaySound("Audio/Music/ab9.wav", NULL, SND_ASYNC);
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
