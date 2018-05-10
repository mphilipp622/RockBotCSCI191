#include "AudioEngine.h"

ISoundEngine* AudioEngine::engine;

AudioEngine::AudioEngine()
{
    // start the sound engine with default parameters
    engine = createIrrKlangDevice();

    if (!engine)
    {
        // Error check for startup problems
       cout << "Audio Engine Failed to Initialize" << endl;
       exit(-1); // error starting up the engine
    }
}

AudioEngine::~AudioEngine()
{
    // For whatever reason, this is necessary in the destructor
    engine->drop();
}

void AudioEngine::SetPosition(double newX, double newY)
{
    // Update the position of the engine to the newX and newY values.
    // Useful for making sure 3D audio is interpreted from the center point of the scene.
    // newX and newY will be passed by player move and jump functions

    vec3df position(newX, newY, 0);
    vec3df lookDirection(0, 0, 6);
    engine->setListenerPosition(position, lookDirection);
    engine->update();
}
