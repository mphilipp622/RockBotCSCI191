#ifndef MELEEENEMY_H
#define MELEEENEMY_H

#include <Enemy.h>
#include <GLScene.h>
#include <Player.h>

class MeleeEnemy : public Enemy
{
    public:
        MeleeEnemy();
        MeleeEnemy(double newX, double newY, double newWidth, double newHeight, string newName);
        virtual ~MeleeEnemy();

        void InitEnemy();

    protected:

    private:
        void AIRoutine();
        bool CheckCollision();
        bool CheckCircleCollision();
        bool CheckCircleSquareCollision();
        bool CheckForwardCollision();
        bool CheckForPit();

        void MoveLeft();
        void MoveRight();
        void StopMove();
};

#endif // MELEEENEMY_H
