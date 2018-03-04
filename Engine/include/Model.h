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

        void Update();

        // Character Controller Functions
        void Jump();
        void Jump2();
        void NormalAttack(bool);
        void StartJump();

        // x Movement
        void StartMove(float dir);
        void MoveLeft();
        void MoveRight();
        void StopMove();
        void SlowDown();

        double rotateX, rotateY, rotateZ;
        double zoom;
        double xPos, yPos;
//        string direction;
        vec vertices[4];
    protected:

    private:
        bool jump, slowDown, moving;
        float jumpVelocity;
        float initialY;
        float xDirection, prevXDirection;
        float acceleration, accelRate, maxAcceleration, deceleration;
        float gravity;

};

#endif // MODEL_H
