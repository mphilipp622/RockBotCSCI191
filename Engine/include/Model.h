#ifndef MODEL_H
#define MODEL_H

#include <windows.h>>
#include "glut.h"

class Model
{
    public:
        Model();
        virtual ~Model();
        void DrawModel();

        double rotateX, rotateY, rotateZ;

        double zoom;

        double xPos, yPos;

    protected:

    private:
};

#endif // MODEL_H
