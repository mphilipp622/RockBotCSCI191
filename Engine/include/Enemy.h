#ifndef ENEMY_H
#define ENEMY_H

#include <Model.h>
#include <vector>
#include <Timer.h>
#include <DeltaTime.h>
#include <AudioSource.h>
#include <GLScene.h>

class Enemy : public Model
{
    public:
        Enemy();
        Enemy(double newX, double newY, double newWidth, double newHeight, string newName);
        virtual ~Enemy();

        void Update();
        virtual void InitEnemy(); // will be used by children classes so they have different sprites
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

        virtual void AIRoutine();

        int idleFrame, dyingFrame;
        int actionTrigger;
        int moveSpeed, jumpSpeed;
        Timer* frameTimer;
        vector<TextureLoader> moveAnim;
        vector<TextureLoader> idleAnim;
        vector<TextureLoader> jumpAnim;
        vector<TextureLoader> deathAnim;
        void Actions(int);

        virtual bool CheckCollision();
        virtual bool CheckCircleCollision();
        virtual bool CheckCircleSquareCollision();

        AudioSource* sound;
    private:

};

#endif // ENEMY_H
