#include "ChordManager.h"

ChordManager::ChordManager()
{
    //ctor
    roots = {"C", "G", "D", "A", "E", "B", "F#", "C#", "G#", "Eb", "Bb", "F"};

    progressions =
    {
        {1, 4, 5, 1},
        {1, 2, 5, 1},
        {1, 6, 4, 5},
        {1, 6, 2, 5},
        {1, 4, 6, 5},
        {1, 5, 6, 4}
    };

    chords =
    {
        { "C",{ "C", "Dm", "Em", "F", "G", "Am", "Bdim" } },
        { "G",{ "G", "Am", "Bm", "C", "D", "Em", "F#dim" } },
        { "D",{ "D", "Em", "F#m", "G", "A", "Bm", "C#dim" } },
        { "A",{ "A", "Bm", "C#m", "D", "E", "F#m", "G#dim" } },
        { "E",{ "E", "F#m", "G#m", "A", "B", "C#m", "D#dim" } },
        { "B",{ "B", "C#m", "D#m", "E", "F#", "G#m", "A#dim" } },
        { "F#",{ "F#", "G#m", "A#m", "B", "C#", "D#m", "Fdim" } },
        { "C#",{ "C#", "D#m", "Fm", "F#", "G#", "A#m", "Cdim" } },
        { "G#",{ "G#", "Bbm", "Cm", "Db", "Eb", "Fm", "Gdim" } },
        { "Eb",{ "Eb", "Fm", "Gm", "G#", "Bb", "Cm", "Ddim" } },
        { "Bb",{ "Bb", "Cm", "Dm", "Eb", "F", "Gm", "Adim" } },
        { "F",{ "F", "Gm", "Am", "Bb", "C", "Dm", "Edim" } }
    };
}

ChordManager::~ChordManager()
{
    //dtor
}

void ChordManager::StartNewSequence()
{
    currentRoot = roots.at(rand() % roots.size()); // randomize new root
    currentProgression = rand() % progressions.size(); // randomize new progression
    progressionIndex = 0; // set progression index back to 0.
}

void ChordManager::StartNewProgression()
{
    currentProgression = rand() % progressions.size();
    progressionIndex = 0;
}

string ChordManager::GetNextChord()
{
    string nextChord = chords[currentRoot].at(progressions.at(currentProgression).at(progressionIndex) - 1);
    progressionIndex++;

    if(progressionIndex >= progressions.at(currentProgression).size())
        StartNewProgression(); // if we've played the whole progression, start a new one

    return nextChord;
}
