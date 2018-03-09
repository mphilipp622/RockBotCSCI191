#ifndef PARALLAX_H
#define PARALLAX_H


#include <windows.h>
#include <string>
#include <GL\GL.h>
#include <string>

using namespace std;

class Parallax
{
    public:
        Parallax();
        virtual ~Parallax();
        void DrawSquare(float, float);
        void ParallaxInit(string fileName);
        void Scroll(bool, string, float);

        float xMax, yMax, xMin, yMin;

    protected:

    private:
};

#endif // PARALLAX_H
