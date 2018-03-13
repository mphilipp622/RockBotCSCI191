#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <Model.h>

using namespace std;

class Projectile : public Model
{
    public:
        Projectile();
        Projectile(double newX, double newY, double newWidth, double newHeight, int newDamage, float newSpeed, string newName, double newTargetX, double newTargetY);
        virtual ~Projectile();

        void Update();

    protected:
        int damage;
        float speed;
        double targetX, targetY;

    private:
};

#endif // PROJECTILE_H
