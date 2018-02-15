#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "SOIL.h"
#include "gl/gl.h"

class TextureLoader
{
    public:
        TextureLoader();
        virtual ~TextureLoader();
        void BindTexture(char*); //char* is filename
        void Binder();
        unsigned char* image;
        int width, height;
        GLuint tex;

    protected:

    private:
};

#endif // TEXTURELOADER_H
