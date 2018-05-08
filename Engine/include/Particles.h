#ifndef PARTICLES_H
#define PARTICLES_H

#include <GL/gl.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <Timer.h>
#include <vector>
#include <TextureLoader.h>
#include <DeltaTime.h>

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

        void DrawParticles();
        void LifeTime();
        void GenerateParticles();
        double DoubleRandom();

        void GenerateMusicParticles(int x, int y, double width, double height);
        void LifetimeMusic(double x, double y, double xDir, double yDir, double width);
        void GenerateSparks(int x, int y, double width, double height);

    protected:

    private:

        struct Node
        {
            bool alive;
            double xPos, yPos, zPos;
            float directionX, directionY;
            float mass;
            Timer* time;
            // particle characteristics
            Node()
            {
                alive = true;
                xPos = 0;
                yPos = 0;
                time = new Timer();
                time->Start();
            }
            Node(double newX, double newY)
            {
                alive = true;
                xPos = newX;
                yPos = newY;
                time = new Timer();
                time->Start();
            }
        };

        vector<Node> drops;

        TextureLoader* texture;

};

#endif // PARTICLES_H
