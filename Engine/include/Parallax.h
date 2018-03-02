#ifndef PARALLAX_H
#define PARALLAX_H
#include <string>
#include <GL/gl.h>
#include <windows.h>

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
