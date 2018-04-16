#include "AudioEngine.h"

ISoundEngine* AudioEngine::engine;

AudioEngine::AudioEngine()
{
    // start the sound engine with default parameters
    engine = createIrrKlangDevice();

    if (!engine)
    {
       cout << "Audio Engine Failed to Initialize" << endl;
       exit(-1); // error starting up the engine
    }
}

AudioEngine::~AudioEngine()
{
    engine->drop();
}

void AudioEngine::SetPosition(double newX, double newY)
{
    vec3df position(newX, newY, 0);
    vec3df lookDirection(0, 0, 6);
    engine->setListenerPosition(position, lookDirection);
    engine->update();
}
