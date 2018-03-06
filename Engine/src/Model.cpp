#include "Model.h"
#include "TextureLoader.h"
#include "DeltaTime.h"
#include <iostream>

using namespace std;

TextureLoader* texture = new TextureLoader();

Model::Model()
{
    // rotations
    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    // translations
    zoom = -4.0;
    xPos = -0.5;
    yPos = -0.5;

    // Create Square
    vertices[0].x = 0.0; vertices[0].y = 0.0; vertices[0].z = 1.0;
    vertices[1].x = 1.0; vertices[1].y = 0.0; vertices[1].z = 1.0;
    vertices[2].x = 1.0; vertices[2].y = 1.0; vertices[2].z = 1.0;
    vertices[3].x = 0.0; vertices[3].y = 1.0; vertices[3].z = 1.0;

}

Model::Model(float newWidth, float newHeight, string newName)
{
    width = newWidth;
    height = newHeight;
    name = newName;

    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    // translations
    zoom = -4.0;
    xPos = 0;
    yPos = 0;

    // Create Square
    vertices[0].x = 0.0; vertices[0].y = 0.0; vertices[0].z = 1.0;
    vertices[1].x = width; vertices[1].y = 0.0; vertices[1].z = 1.0;
    vertices[2].x = width; vertices[2].y = height; vertices[2].z = 1.0;
    vertices[3].x = 0.0; vertices[3].y = height; vertices[3].z = 1.0;
}

Model::~Model()
{

}
void Model::DrawModel()
{
    //render this model
    glColor3f(1.0, 1.0, 1.0);
    texture->Binder(); // update texture
    glTranslated(xPos, yPos, zoom);
    glRotated(rotateX, 1, 0, 0);
    glRotated(rotateY, 0, 1, 0);
    glRotated(rotateZ, 0, 0, 1);


    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

    glEnd();
    //Uncomment the below to make teapot object
    //glScalef(1.0, 1.0, 0.0);
    //glutSolidTeapot(1.0);

    //This draws out a perfect 2D square.
//    glBegin(GL_POLYGON);
//    glVertex3f(-0.500000, -0.500000, 0.500000);
//    glVertex3f(0.500000, -0.500000, 0.500000);
//    glVertex3f(0.500000, 0.500000, 0.500000);
//    glVertex3f(-0.500000, 0.500000, 0.500000);
//    glEnd();
}

void Model::InitModel(char* fileName, bool transparent)
{
    if(transparent)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // blends object to background color instead
    }
    texture->Binder();
     cout << "Loading Model: " << fileName << endl;
    texture->BindTexture(fileName);

}

bool Model::Collision(Model* collider)
{
    return Overlapping(xPos, xPos + width, collider->GetX(), collider->GetX() + collider->GetWidth()) &&
           Overlapping(yPos, yPos + height, collider->GetY(), collider->GetY() + collider->GetHeight());
}

bool Model::Overlapping(double min0, double max0, double min1, double max1)
{
    return (max0 >= min1 && min0 <= max1);
}

bool Model::OverlapGround(double maxY, double minY)
{
    return (maxY >= minY);
}

bool Model::GroundCheck(Model* collider)
{
    return OverlapGround(yPos + height, -collider->GetY());
}


double Model::GetX()
{
    return xPos;
}

double Model::GetY()
{
    return yPos;
}

double Model::GetWidth()
{
    return width;
}

double Model::GetHeight()
{
    return height;
}

string Model::GetName()
{
    return name;
}

void Model::SetPosition(double newX, double newY)
{
    xPos = newX;
    yPos = newY;
}
