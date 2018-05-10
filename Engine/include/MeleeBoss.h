#ifndef MELEEBOSS_H
#define MELEEBOSS_H

#include <Enemy.h>
#include <GLScene.h>
#include <Player.h>

class MeleeBoss : public Enemy
{
    public:
        MeleeBoss();
        MeleeBoss(double newX, double newY, double newWidth, double newHeight, string newName);
        virtual ~MeleeBoss();

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

#endif // MELEEBOSS_H
