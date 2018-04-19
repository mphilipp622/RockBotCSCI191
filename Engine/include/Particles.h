#ifndef PARTICLES_H
#define PARTICLES_H

#include <GL/gl.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

#define MAX_DROPS 50000
#define GRAVITY -0.001

using namespace std;

class Particles
{
    public:
        Particles();
        virtual ~Particles();

        int numDrops;

        typedef struct
        {
            // particle characteristics
            bool alive;
            float xPos, yPos, zPos;
            float directionX, directionY;
            float mass;
        } particle;

        particle drops[MAX_DROPS];

        void DrawParticles();
        void LifeTime();
        void GenerateParticles();
        double DoubleRandom();

    protected:

    private:
};

#endif // PARTICLES_H
