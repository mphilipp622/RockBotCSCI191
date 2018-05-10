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
#include <algorithm>

#define MAX_MUSIC_DROPS 500
#define MAX_DROPS 50000
#define GRAVITY -2.0
#define MAX_SPARKS 50

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

        void GenerateSparks(int x, int y, double playerDir);
        void LifetimeSparks();
        bool GetIsDead();
        void DrawSparks();

    protected:

    private:

        double RadiusRandom();
//        double projectileX, projectileY;

        struct Node
        {
            bool alive;
            double xPos, yPos, zPos;
            float directionX, directionY;
            double angleOfRotation, rotationZ;
            double acceleration, accelerationX, accelRate;
            float mass;
            TextureLoader sparkTex;
            string name;
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
            Node(double newX, double newY, string newName)
            {
                alive = true;
                xPos = newX;
                yPos = newY;
                time = new Timer();
                time->Start();
                name = newName;
                acceleration = 2.0;
                accelerationX = 2.0;
                accelRate = 0.1;
            }

            bool operator==(const struct Node& other) const
            {
                return name == other.name;
            }

            void SetTexture(string newTex)
            {
                sparkTex.BindTexture(newTex);
            }
        };

        vector<Node> drops;

        TextureLoader* texture;
        vector<string> sparkFiles;

        bool isDead;
};

#endif // PARTICLES_H
