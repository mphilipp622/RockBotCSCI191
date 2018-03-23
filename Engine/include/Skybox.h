#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL\GL.h>
#include <TextureLoader.h>

class Skybox
{
    public:
        Skybox();
        virtual ~Skybox();

        void LoadTextures();
        void DrawBox();

    protected:

    private:
        float width, height, depth;
        GLuint tex[6];
        float rotateX, rotateY, rotateZ;
        float translateX, translateY, translateZ;
};

#endif // SKYBOX_H
