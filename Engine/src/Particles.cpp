#include "Particles.h"
#include <iomanip>
#include <cmath>

Particles::Particles()
{
    //ctor
    numDrops = 0;
    texture = new TextureLoader();
    texture->BindTexture("Images/Misc/MusicParticle3.png");
}

Particles::~Particles()
{
    //dtor
}

void Particles::DrawParticles()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor4f(1.0, 1.0, 1.0, 1.0);
    texture->Binder();
//    glPointSize(5); // pixel size of particle

//    glBegin(GL_POINTS);

    for(auto drop : drops)
    {
//        glRotated(0, 1, 0, 0);
//        glRotated(0, 0, 1, 0);
//        glRotated(drop.angleOfRotation, 0, 0, 1.0);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
		glVertex3f(drop.xPos, drop.yPos, 0);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(drop.xPos + 0.08, drop.yPos, 0);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(drop.xPos + 0.08, drop.yPos - 0.08, 0);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(drop.xPos, drop.yPos - 0.08, 0);
		glEnd();
//        glVertex3f(drop.xPos, drop.yPos, 0);
    }



    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
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

void Particles::LifetimeMusic(double x, double y, double xDir, double yDir, double width)
{
    double radius = width / 2;
    double theta = 0;

    for(int i = 0; i < numDrops; i++)
    {
        if(drops[i].alive)
        {
            double newX = x + (radius * RadiusRandom()) * cos(theta);
            double newY = y + (radius * RadiusRandom()) * sin(theta);
//            double newX = (x - drops[i].xPos) - newDir;
//            double newY = (y - drops[i].yPos) - newDir;
            drops[i].angleOfRotation = theta;
            drops[i].xPos = newX;
            drops[i].yPos = newY;
//            cout << abs((x - drops[i].xPos) - xDir) << "    " << abs((y - drops[i].yPos) - yDir) << endl;
//            drops[i].xPos -= abs((x - drops[i].xPos) - xDir) * DeltaTime::GetDeltaTime();
//            drops[i].yPos -= abs((y - drops[i].yPos) - yDir) * DeltaTime::GetDeltaTime();
        }

        theta += (360 / numDrops);
    }
}


void Particles::GenerateParticles()
{
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

double Particles::RadiusRandom()
{
    // returns a number between 0.7 and 1.0
    // 0.3 is 1.0 - 0.7
    return ((rand() / double(RAND_MAX)) * 0.5) + 0.5;
}



////////////////////////////////////////////
// MUSIC NOTE PARTICLE GENERATION
///////////////////////////////////////////

void Particles::GenerateMusicParticles(int x, int y, double width, double height)
{

    double radius = width / 2;

    int newDrops = 25; // 60 is arbitrary. Could put anything
    double theta = 0;



    if(numDrops + newDrops > MAX_MUSIC_DROPS)
        newDrops = MAX_MUSIC_DROPS - numDrops;

    for(int i = 0; i < newDrops; i++)
    {
        // This equation will create a circle of particles around the boundaries of the music note
        double newX = x + radius * cos(theta);
        double newY = y + radius * sin(theta);


        drops.push_back(Node(newX, newY));
//        drops[i].alive = true;
//        drops[i].xPos = newX;
//        drops[i].yPos = newY;
//        drops[i].directionX = 0; // these constant values are pretty much test and check
//        drops[i].directionY = 0;
//        drops[i].mass = 0.5 + 0.5 * DoubleRandom();
//        drops[i].time = new Timer();
//        drops[i].time->Start();

        theta += (360 / newDrops); // move onto the next part of the circle

//        if(theta > 360) // if we've exceeded a full circle of particles, then stop generating
//            break;
    }

    numDrops += newDrops;

    if(numDrops >= MAX_MUSIC_DROPS)
        numDrops = MAX_MUSIC_DROPS;

}

void Particles::GenerateSparks(int x, int y, double width, double height)
{

//    int newDrops = 100; // 60 is arbitrary. Could put anything
//
//    if(numDrops + newDrops > MAX_MUSIC_DROPS)
//        newDrops = MAX_MUSIC_DROPS - numDrops;
//
//    int randVal[2] = {-1, 1};
//    for(int i = 0; i < newDrops; i++)
//    {
//        drops.push_back(Node(newX, newY));
//        drops.back().directionX = (double) ((rand() % 1.0) * randVal[rand() % 2]);
//        drops.back().directionY = (double) ((rand() % 1.0) * randVal[rand() % 2]);
////        drops[i].alive = true;
////        drops[i].xPos = newX;
////        drops[i].yPos = newY;
////        drops[i].directionX = 0; // these constant values are pretty much test and check
////        drops[i].directionY = 0;
//        drops[i].mass = 0.5 + 0.5 * DoubleRandom();
//        drops[i].time = new Timer();
//        drops[i].time->Start();
//
//    }
//
//    numDrops += newDrops;
//
//    if(numDrops >= MAX_MUSIC_DROPS)
//        numDrops = MAX_MUSIC_DROPS;
}
