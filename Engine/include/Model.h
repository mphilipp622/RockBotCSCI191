#ifndef MODEL_H
#define MODEL_H

#include <windows.h>
#include "glut.h"

typedef struct
{
    float x, y, z;
}vec;

class Model
{
    public:
        Model();
        virtual ~Model();
        void DrawModel();
        void InitModel(char* fileName, bool transparent);

        void InitPlayer();

        double rotateX, rotateY, rotateZ;
        double zoom;
        double xPos, yPos;
//        string direction;
        vec vertices[4];
    protected:

    private:

};

#endif // MODEL_H
