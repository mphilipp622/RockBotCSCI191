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
        Model(float, float, double, double, string);
        virtual ~Model();
        void DrawModel();
        void InitModel(char* fileName, bool transparent);

        void InitPlayer();

        double rotateX, rotateY, rotateZ;
        double zoom;
//        string direction;
        vec vertices[4];

        // collision getters
        double GetX();
        double GetY();
        float GetWidth();
        float GetHeight();
        void SetPosition(double, double);
        void SetWidth(double);

        string GetName();
    protected:
        float width, height;
        double xPos, yPos;
        string name;
        bool GroundCheck(Model*);
        bool Collision(Model*);

    private:
        bool Overlapping(double min0, double max0, double min1, double max1);
        bool OverlapGround(double maxY, double minY);
};

#endif // MODEL_H
