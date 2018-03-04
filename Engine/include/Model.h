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

        // Character Controller Functions
        void Jump();
        void Jump2();
        void NormalAttack(bool);
        void SetJump(bool);
        void Move(float direction);
        void StopMove();
        void SlowDown();

        void Update();

        double acceleration;
        double rotateX, rotateY, rotateZ;
        double zoom;
        double xPos, yPos;
//        string direction;
        vec vertices[4];
        float gravity;
    protected:

    private:
        bool jump, slowDown;
        float jumpY;
        float initialY;
        float xDirection;

};

#endif // MODEL_H
