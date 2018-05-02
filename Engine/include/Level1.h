#ifndef LEVEL1_H
#define LEVEL1_H

#include <GLScene.h>

class Level1 : public GLScene
{
    public:
        Level1();
        virtual ~Level1();

        virtual GLint initGL();
        virtual GLint drawGLScene();

         // keyboard and mouse inputs
        virtual int windowsMsg(HWND, UINT, WPARAM, LPARAM);

        // used for loading into a scene from this scene
        virtual void LoadScene(string name);

    protected:

    private:
};

#endif // LEVEL1_H
