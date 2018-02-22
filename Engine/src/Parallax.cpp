#include "Parallax.h"
#include "TextureLoader.h"

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
    glColor3f(1.0, 1.0, 1.0);

    backgroundTexture->Binder();

    glBegin(GL_POLYGON); // begin drawing square

    glTexCoord2f(xMin, yMin);
    glVertex3f(-width / height, -1.0f, -8.0f); // has z depth. Used for parallaxing. If character is on z = 0, will look good

    glTexCoord2f(xMax, yMin);
    glVertex3f(width / height, -1.0f, -8.0f); // has z depth. Could use 2f for 2D

    glTexCoord2f(xMax, yMax);
    glVertex3f(width / height, 1.0f, -8.0f); // has z depth. Could use 2f for 2D

    glTexCoord2f(xMin, yMax);
    glVertex3f(-width / height, 1.0f, -8.0f); // has z depth. Could use 2f for 2D

    glEnd();
}

void Parallax::ParallaxInit(char* fileName)
{
    backgroundTexture->Binder();
    backgroundTexture->BindTexture(fileName);
}

void Parallax::Scroll(bool, string, float)
{

}
