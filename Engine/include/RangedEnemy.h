#ifndef RANGEDENEMY_H
#define RANGEDENEMY_H

#include <Enemy.h>
#include <GLScene.h>
#include <Player.h>
#include <Projectile.h>

// The ranged enemy will patrol back and forth on the x axis and stop to shoot at player when the player is in aggro range
class RangedEnemy : public Enemy
{
    public:
        RangedEnemy();
        RangedEnemy(double newX, double newY, double newWidth, double newHeight, string newName);
        virtual ~RangedEnemy();

        void InitEnemy();

    protected:

    private:
        double xPathDistance; // the distance the drone will travel in one direction before turning around
        double xPatrolCenter; // used for determining the patrol area of the drone

        Timer* attackTimer; // will track attack speed time
        double attackSpeed; // attack speed of the drone. Will be used to implement a cooldown period. Consider this attack per second

        // AI Functions
        void AIRoutine();
        void Patrol(); // Patrol back and forth on x axis
        void ShootProjectile(double xTarget, double yTarget);

        // Collision Functions
        bool CheckCollision();
        bool CheckCircleCollision();
        bool CheckCircleSquareCollision();
        bool CheckForwardCollision();
        bool CheckForPit();


};

#endif // RANGEDENEMY_H
