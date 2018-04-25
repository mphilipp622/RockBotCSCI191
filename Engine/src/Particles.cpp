#include "Particles.h"

Particles::Particles()
{
    //ctor
    numDrops = 1;
}

Particles::~Particles()
{
    //dtor
}

void Particles::DrawParticles()
{
    glColor3f(1.0, 1.0 , 1.0);
    glPointSize(3); // pixel size of particle

    glBegin(GL_POINTS);

    int i = 0;
    while(i < numDrops)
    {
        if(drops[i].alive)
        {

            glVertex3f(drops[i].xPos, drops[i].yPos, 0);
        }
        i++;
    }

    glEnd();
}

// Setting Movement
void Particles::LifeTime()
{
    for(int i = 0; i < numDrops; i++)
    {
        if(drops[i].alive)
        {
            if(drops[i].yPos + GRAVITY * drops[i].mass < 0.0)
            {
                // make particle bounce
                drops[i].directionY = -drops[i].directionY;
            }
            else
            {
                drops[i].directionY += GRAVITY * drops[i].mass;
            }

            drops[i].xPos += drops[i].directionX;
            drops[i].yPos += drops[i].directionY;

//            if(drops[i].yPos < -5.0 && drops[i].xPos > 5.0)
//                drops[i].alive = false; // bounds checking to destroy particle. Probably change later.
        }
    }
}

void Particles::GenerateParticles()
{
    int i = 0;

    int newDrops = DoubleRandom() * 60; // 60 is arbitrary. Could put anything

    if(numDrops + newDrops > MAX_DROPS)
        newDrops = MAX_DROPS - numDrops;

    for(int i = numDrops; i < numDrops + newDrops; i++)
    {
        drops[i].alive = true;
        drops[i].xPos = -0.8 + 0.1 * DoubleRandom();
        drops[i].yPos = 0.8 + 0.1 * DoubleRandom();
        drops[i].directionX = 0.0075 + 0.025 * DoubleRandom(); // these constant values are pretty much test and check
        drops[i].directionY = 0;
        drops[i].mass = 0.5 + 0.5 * DoubleRandom();
    }

    numDrops += newDrops;

    if(numDrops >= MAX_DROPS)
        numDrops = 0;
}

double Particles::DoubleRandom()
{
    return rand() % 1000 / 1000.0;
}

void Particles::GenerateMusicParticles()
{

}
