#ifndef ENEMY_H
#define ENEMY_H

#include <Model.h>
#include <vector>
#include <Timer.h>
#include <DeltaTime.h>
#include <AudioSource.h>

class Enemy : public Model
{
    public:
        Enemy();
        Enemy(double newX, double newY, double newWidth, double newHeight, string newName);
        virtual ~Enemy();

        void Update();
        virtual void InitEnemy() = 0; // will be used by children classes so they have different sprites
        void DrawEnemy();

        void TakeDamage(int damageTaken);

    protected:
        bool jump, slowDown, moving, startGravity;
        float jumpVelocity, fallVelocity;
        float initialY;
        float xDirection, prevXDirection;
        float prevXPos, prevYPos;
        float acceleration, accelRate, maxAcceleration, deceleration;
        float gravity;

        // x Movement
        void StartMove(float dir);
        void MoveLeft();
        void MoveRight();
        void StopMove();
        void SlowDown();

        // y movement
        void ApplyGravity();
        void Jump();
        void StartJump();

        int hp;
        bool isDying;
        void Die();

        virtual void AIRoutine() = 0;

        int idleFrame, dyingFrame;
        int actionTrigger;
        int moveSpeed, jumpSpeed;
        Timer* frameTimer;
        TextureLoader moveAnim[4];
        TextureLoader idleAnim[1];
        TextureLoader jumpAnim[1];
        TextureLoader deathAnim[3];
        void Actions(int);

        virtual bool CheckCollision() = 0;
        virtual bool CheckCircleCollision() = 0;
        virtual bool CheckCircleSquareCollision() = 0;

        AudioSource* sound;
    private:

};

#endif // ENEMY_H
