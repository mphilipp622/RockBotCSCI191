#ifndef CHORDMANAGER_H
#define CHORDMANAGER_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

class ChordManager
{
    public:
        ChordManager();
        virtual ~ChordManager();

        // called on by Player class when user presses shift. Will set a new root note and new progression.
        void StartNewSequence();

        // Returns the name of the next chord in the current progression. Will be used by Player class.
        string GetNextChord();

    protected:

    private:
        vector<string> majorRoots, minorRoots; // contains the 12 root note names.
        vector<vector<int>> progressions; // contains common chord progressions.
        unordered_map<string, vector<string>> minorChords, majorChords; // contains all 7 chords for all 12 root notes

        string currentRoot;
        int currentProgression;
        int progressionIndex; // Will keep track of where we are within a progression
        bool majorOrMinor; // maybe use this to change the feeling of a level. Or to affect the player somehow. 0 = major, 1 = minor

        /*
        will keep the same root but change which progression we're using. Will happen after a progression finishes.
        This allows us to stay in the same key but played different chord changes. Should keep the sound consistent as long as the user continues holding shift.
        */
        void StartNewProgression();

};

#endif // CHORDMANAGER_H
