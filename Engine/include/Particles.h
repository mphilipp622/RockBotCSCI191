#ifndef PARTICLES_H
#define PARTICLES_H

#include <GL/gl.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <Timer.h>

#define MAX_MUSIC_DROPS 500
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
            Timer* time;
        } particle;

        particle drops[MAX_MUSIC_DROPS];

        void DrawParticles();
        void LifeTime();
        void GenerateParticles();
        double DoubleRandom();

        void GenerateMusicParticles(int x, int y, double width, double height);
        void LifetimeMusic(double x, double y, double width);

    protected:

    private:
};

#endif // PARTICLES_H
