#ifndef MELEEENEMY_H
#define MELEEENEMY_H

#include <Enemy.h>
#include <GLScene.h>

class Enemy;

class MeleeEnemy : public Enemy
{
    public:
        MeleeEnemy();
        MeleeEnemy(double newX, double newY, double newWidth, double newHeight, string newName);
        virtual ~MeleeEnemy();


    protected:

    private:
        void InitEnemy();
        bool CheckCollision();
        bool CheckCircleCollision();
        bool CheckCircleSquareCollision();
};

#endif // MELEEENEMY_H
