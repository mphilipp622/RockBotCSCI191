#include "Particles.h"
#include <iomanip>

Particles::Particles()
{
    //ctor
    numDrops = 0;
    texture = new TextureLoader();
    texture->BindTexture("Images/Misc/MusicParticle.png");
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

glBegin(GL_QUADS);
//    glBegin(GL_POINTS);

    for(auto drop : drops)
    {
        if(!drop.alive)
            continue;

        glTexCoord2f(0.0, 1.0);
		glVertex3f(drop.xPos, drop.yPos, 0);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(drop.xPos + 0.03, drop.yPos, 0);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(drop.xPos + 0.03, drop.yPos - 0.03, 0);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(drop.xPos, drop.yPos - 0.03, 0);
//        glVertex3f(drop.xPos, drop.yPos, 0);
    }


    glEnd();
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
    double theta = sqrt((xDir * xDir) + (yDir * yDir)) * 1000;

    cout << theta << endl;

    for(int i = 0; i < numDrops; i++)
    {
        if(drops[i].alive)
        {
            double newX = x + radius * cos(theta);
            double newY = y + radius * sin(theta);
//            double newX = x + radius * cos(theta);
//            double newY = y + radius * sin(theta);
//            double newX = (x - drops[i].xPos) - newDir;
//            double newY = (y - drops[i].yPos) - newDir;
//            double newX = x * DoubleRandom();
//            double newY = y * DoubleRandom();
            drops[i].xPos = newX;
            drops[i].yPos = newY;
//            drops[i].xPos -= xDir;
//            drops[i].yPos -= yDir;
//            drops[i].xPos -= (x - drops[i].xPos) * xDir;
//            drops[i].yPos -= (y - drops[i].yPos) * yDir;

//            if(drops[i].time->GetTicks() > 100)
//                drops[i].alive = false;

        }

        theta += 1.8;
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




////////////////////////////////////////////
// MUSIC NOTE PARTICLE GENERATION
///////////////////////////////////////////

void Particles::GenerateMusicParticles(int x, int y, double width, double height)
{

    double radius = width / 4;

    int newDrops = 100; // 60 is arbitrary. Could put anything
    double theta = 0;

    if(numDrops + newDrops > MAX_MUSIC_DROPS)
        newDrops = MAX_MUSIC_DROPS - numDrops;

    for(int i = 0; i < newDrops; i++)
    {
        // This equation will create a circle of particles around the boundaries of the music note
//        double newX = x + radius * cos(theta);
//        double newY = y + radius * sin(theta);


//        drops.push_back(Node(newX, newY));
        cout << DoubleRandom() << endl;
        double newX = x * DoubleRandom();
        double newY = y * DoubleRandom();
        drops.push_back(Node(newX, newY));


//        drops[i].alive = true;
//        drops[i].xPos = newX;
//        drops[i].yPos = newY;
//        drops[i].directionX = 0; // these constant values are pretty much test and check
//        drops[i].directionY = 0;
//        drops[i].mass = 0.5 + 0.5 * DoubleRandom();
//        drops[i].time = new Timer();
//        drops[i].time->Start();

        theta += 3.6; // move onto the next part of the circle

//        if(theta > 360) // if we've exceeded a full circle of particles, then stop generating
//            break;
    }

    numDrops += newDrops;

    if(numDrops >= MAX_MUSIC_DROPS)
        numDrops = 0;

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
