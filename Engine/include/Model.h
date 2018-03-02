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
        virtual ~Model();
        void DrawModel();
        void InitModel(string fileName, bool transparent);
        void Jump();
        void Jump2();
        void Update();
        void NormalAttack(bool);
        void SetJump(bool);

        double acceleration;
        double rotateX, rotateY, rotateZ;
        double zoom;
        double xPos, yPos;
//        string direction;
        vec vertices[4];
        float gravity;
    protected:

    private:
        bool jump;
        float jumpY;
        float initialY;

};

#endif // MODEL_H
