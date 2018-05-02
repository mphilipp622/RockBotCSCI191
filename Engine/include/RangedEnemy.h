#ifndef RANGEDENEMY_H
#define RANGEDENEMY_H

#include <Enemy.h>
#include <GLScene.h>
#include <Player.h>

class RangedEnemy : public Enemy
{
    public:
        RangedEnemy();
        RangedEnemy(double newX, double newY, double newWidth, double newHeight, string newName);
        virtual ~RangedEnemy();

        void InitEnemy();

    protected:

    private:
        void AIRoutine();
        bool CheckCollision();
        bool CheckCircleCollision();
        bool CheckCircleSquareCollision();
};

#endif // RANGEDENEMY_H
