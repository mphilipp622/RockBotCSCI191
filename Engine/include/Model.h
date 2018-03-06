#ifndef MODEL_H
#define MODEL_H

#include <windows.h>
#include "glut.h"
#include <string>

using namespace std;

typedef struct
{
    float x, y, z;
}vec;

class Model
{
    public:
        Model();
        Model(float, float, string);
        virtual ~Model();
        void DrawModel();
        void InitModel(char* fileName, bool transparent);

        void InitPlayer();

        double rotateX, rotateY, rotateZ;
        double zoom;
        double xPos, yPos;
//        string direction;
        vec vertices[4];

        // collision getters
        double GetX();
        double GetY();
        double GetWidth();
        double GetHeight();

        bool Collision(Model*);

        string GetName();
    protected:
        float width, height;
        string name;
    private:
        bool Overlapping(double min0, double max0, double min1, double max1);
};

#endif // MODEL_H
