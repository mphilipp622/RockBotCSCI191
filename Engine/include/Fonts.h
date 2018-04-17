#ifndef FONTS_H
#define FONTS_H

#include <string>
#include <iostream>
#include <TextureLoader.h>

using namespace std;

typedef struct
{
    char letter; // optional
    float xMin, xMax, yMin, yMax; // for texture code.
    float offsetX;
    float fontSize;
} charSet;

class Fonts
{
    public:
        Fonts();
        virtual ~Fonts();

        void InitFonts(char* filename);
        void BuildFont(char* newLine);
        void DrawFont(int i);
        charSet C[1024];
        int charCount;

        float xPos, yPos, zPos;

        float zoom;

    protected:

    private:
        TextureLoader* texture;
};

#endif // FONTS_H
