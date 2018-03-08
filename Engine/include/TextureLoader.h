#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "SOIL.h"
#include "gl/gl.h"
#include <iostream>
#include <string>

using namespace std;

class TextureLoader
{
    public:
        TextureLoader();
        virtual ~TextureLoader();
        void BindTexture(string); //char* is filename
        void Binder();
        unsigned char* image;
        int width, height;
        GLuint tex;

    protected:

    private:
};

#endif // TEXTURELOADER_H
