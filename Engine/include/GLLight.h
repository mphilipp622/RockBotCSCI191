// updated 2/7/18

#ifndef GLLIGHT_H
#define GLLIGHT_H

#include<GLScene.h>

class GLLight : public GLScene
{
    public:
        GLLight(GLenum);
        virtual ~GLLight();

        GLfloat light_ambient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat light_diffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat light_specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat light_position[4] = {2.0f, 5.0f, 5.0f, 0.0f};

        GLfloat mat_ambient[4] = {.7f, .7f, .7f, 1.0f};
        GLfloat mat_diffuse[4] = {0.8f, .8f, .8f, 1.0f};
        GLfloat mat_specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat high_shininess[1] = {100.0f};

        GLvoid SetLight(GLenum);

    protected:

    private:
};

#endif // GLLIGHT_H
