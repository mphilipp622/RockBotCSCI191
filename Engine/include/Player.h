#ifndef PLAYER_H
#define PLAYER_H

#include "GL/gl.h"
#include <Model.h>
#include <TextureLoader.h>
#include <DeltaTime.h>

typedef struct
{
    float x, y, z;
}vec1;

// class for player character. Inherits from Model for positions/rotations/etc.
class Player : public Model
{
    public:
        Player();
        virtual ~Player();

        float scaleSize[3] = {1.0, 1.0, 1.0}; // x, y, z scale values
        vec1 vertices[4]; // 4 vertices of xyz values

        // player stats
        int hp;
        int moveSpeed, jumpSpeed;

        void DrawPlayer();
        void InitPlayer();

        int actionTrigger;
        void Actions(int);

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
//        void SetVertices();
    protected:

    private:
        bool jump, slowDown, moving;
        float jumpVelocity;
        float initialY;
        float xDirection, prevXDirection;
        float acceleration, accelRate, maxAcceleration, deceleration;
        float gravity;

        void CheckCollision();
};

#endif // PLAYER_H
