#include "Parallax.h"
#include "TextureLoader.h"
#include "DeltaTime.h"

TextureLoader *backgroundTexture = new TextureLoader();

Parallax::Parallax()
{
    xMax = 1.0f;
    yMax = 0.0f;
    xMin = 0.0f;
    yMin = 1.0f;
}

Parallax::~Parallax()
{
    //dtor
}

void Parallax::DrawSquare(float width, float height)
{
    //glColor3f(1.0, 1.0, 1.0);

    backgroundTexture->Binder();

    glBegin(GL_POLYGON); // begin drawing square
    //Changed coordinations to push back the background further to open more room between the game scene and background
    glTexCoord2f(xMin, yMin);
    glVertex3f(3*(-width / height), -3.0f, -20.0f); // has z depth. Used for parallaxing. If character is on z = 0, will look good

    glTexCoord2f(xMax, yMin);
    glVertex3f(3*(width / height), -3.0f, -20.0f); // has z depth. Could use 2f for 2D

    glTexCoord2f(xMax, yMax);
    glVertex3f(3*(width / height), 3.0f, -20.0f); // has z depth. Could use 2f for 2D

    glTexCoord2f(xMin, yMax);
    glVertex3f(3*(-width / height), 3.0f, -20.0f); // has z depth. Could use 2f for 2D

    glEnd();
}

void Parallax::ParallaxInit(char* fileName)
{
    backgroundTexture->Binder();
    cout << "Loading Parallax: " << fileName << endl;
    backgroundTexture->BindTexture(fileName);
}

// Scrolls the background based on directions
void Parallax::Scroll(bool Auto, string dir, float speed)
{
    if(Auto)
    {
        if(dir == "up")
        {
            yMin -= speed * DeltaTime::GetDeltaTime();
            yMax -= speed * DeltaTime::GetDeltaTime();
        }
        if(dir == "down")
        {

            yMin += speed * DeltaTime::GetDeltaTime();
            yMax += speed * DeltaTime::GetDeltaTime();
        }
        if(dir == "left")
        {
            xMin -= speed * DeltaTime::GetDeltaTime();;
            xMax -= speed * DeltaTime::GetDeltaTime();;
        }
        if(dir == "right")
        {
            xMin += speed * DeltaTime::GetDeltaTime();;
            xMax += speed * DeltaTime::GetDeltaTime();;
        }
    }
}
