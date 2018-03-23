#ifndef PLAYER_H
#define PLAYER_H

#include <GL\GL.h>
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
        Player(double, double);
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
<<<<<<< HEAD
=======
        void ShootProjectile(double x, double y);
>>>>>>> master
        void NormalAttack(bool);
        void StartJump();

        // x Movement
        void StartMove(float dir);
        void MoveLeft();
        void MoveRight();
        void StopMove();
        void SlowDown();

        void ApplyGravity();
<<<<<<< HEAD
=======

        static Player* player;
        double GetOffsetX();
        double GetOffsetY();
        double GetZoom();
>>>>>>> master
//        void SetVertices();
    protected:

    private:
<<<<<<< HEAD
        bool jump, slowDown, moving;
        float jumpVelocity;
=======
        bool jump, slowDown, moving, startGravity;
        float jumpVelocity, fallVelocity;
>>>>>>> master
        float initialY;
        float xDirection, prevXDirection;
        float prevXPos, prevYPos;
        float acceleration, accelRate, maxAcceleration, deceleration;
        float gravity;
<<<<<<< HEAD

        void CheckCollision();
=======
        float playerZoom;

        int idleFrame;
        bool CheckCollision();
//        bool CheckCollisionY();
//        bool CheckCollisionX();
>>>>>>> master
};

#endif // PLAYER_H
