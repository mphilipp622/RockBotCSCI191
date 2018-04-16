#include "ChordManager.h"

ChordManager::ChordManager()
{
    majorOrMinor = 0;

    majorRoots = {"C", "G", "D", "A", "E", "B", "F#", "C#", "G#", "Eb", "Bb", "F"};
    minorRoots = {"Am", "Bbm", "Bm", "Cm", "C#m", "Dm", "Ebm", "Em", "Fm", "F#m", "Gm", "G#m"}; // record Ebm,

    progressions =
    {
        {1, 4, 5, 1},
        {1, 4, 6, 4},
        {1, 4, 7, 4},
        {1, 2, 5, 1},
        {1, 6, 4, 5},
        {1, 6, 2, 5},
        {1, 4, 6, 5},
        {1, 5, 6, 4},
        {1, 5, 6, 3, 4, 1, 4, 5},
        {2, 4, 5},
        {1, 4, 5, 4},
        {5, 4, 1},
        {6, 4, 1, 5},
        {6, 5, 4, 3},
        {6, 5, 6, 5},
        {2, 1, 5, 7},
        {1, 4, 5},
        {1, 4, 5},
    };

    // These are Major chord progressions.
    majorChords =
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

    minorChords =
    {             //  i       ii dim      iii aug     iv      V       VI      vii dim
        { "Am"  ,{    "Am",   "Bdim",     "Caug",     "Dm",   "E",    "F",    "G#dim" } },
        { "Bbm" ,{   "Bbm",  "Cdim",     "Dbaug",    "Ebm",  "F",    "Gb",   "Adim" } },
        { "Bm"  ,{    "Bm",   "C#dim",    "Daug",     "Em",   "F#",   "G",    "A#dim" } },
        { "Cm"  ,{    "Cm",   "Ddim",     "Ebaug",    "Fm",   "G",    "Ab",   "Bdim" } },
        { "C#m" ,{   "C#m",  "D#dim",    "Eaug",     "F#m",  "G#",   "A",    "B#dim" } },
        { "Dm"  ,{    "Dm",   "Edim",     "Faug",     "Gm",   "A",    "Bb",   "C#dim" } },
        { "Ebm" ,{   "Ebm",  "Fdim",     "Gbaug",    "Abm",  "Bb",   "Cb",   "Ddim" } },
        { "Em"  ,{    "Em",   "F#dim",    "Gaug",     "Am",   "B",    "C",    "D#dim" } },
        { "Fm"  ,{    "Fm",   "Gdim",     "Abaug",    "Bbm",  "C",    "Db",   "Edim" } },
        { "F#m" ,{   "F#m",  "G#dim",    "Aaug",     "Bm",   "C#",   "D",    "Fdim" } },
        { "Gm"  ,{    "Gm",   "Adim",     "Bbaug",    "Cm",   "D",    "Eb",   "F#dim" } },
        { "G#m" ,{   "G#m",  "A#dim",    "Baug",     "C#m",  "D#",   "E",    "Fxdim" } }
    };
}

ChordManager::~ChordManager()
{
    //dtor
}

void ChordManager::StartNewSequence()
{
//    majorOrMinor = rand() % 2;
    if(majorOrMinor == 0)
        // 0 is major
        currentRoot = majorRoots.at(rand() % majorRoots.size()); // randomize new root
//    else
//        // 1 is minor
//        currentRoot = minorRoots.at(rand() % minorRoots.size()); // randomize minor root.

//    currentRoot = roots.at(rand() % roots.size());
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
    string nextChord;
    if(majorOrMinor == 0 )
        nextChord = majorChords[currentRoot].at(progressions.at(currentProgression).at(progressionIndex) - 1);
//    else
//        nextChord = minorChords[currentRoot].at(progressions.at(currentProgression).at(progressionIndex) - 1);

    progressionIndex++;

    if(progressionIndex >= progressions.at(currentProgression).size())
        StartNewProgression(); // if we've played the whole progression, start a new one

    return nextChord;
}
