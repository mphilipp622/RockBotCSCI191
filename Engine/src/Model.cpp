#include "Model.h"
#include "TextureLoader.h"
#include "DeltaTime.h"
#include <iostream>
#include <algorithm> // max and min
#include <Player.h>

using namespace std;

TextureLoader* texture = new TextureLoader();

Model::Model()
{
//    // rotations
//    rotateX = 0;
//    rotateY = 0;
//    rotateZ = 0;
//
//    // translations
//    zoom = -3.0;
//    xPos = -0.5;
//    yPos = -0.5;
//
//    // Create Square
//    vertices[0].x = 0.0; vertices[0].y = 0.0; vertices[0].z = 1.0;
//    vertices[1].x = 1.0; vertices[1].y = 0.0; vertices[1].z = 1.0;
//    vertices[2].x = 1.0; vertices[2].y = 1.0; vertices[2].z = 1.0;
//    vertices[3].x = 0.0; vertices[3].y = 1.0; vertices[3].z = 1.0;

}

Model::Model(float newWidth, float newHeight, double newX, double newY, string newName)
{
    width = newWidth;
    height = newHeight;

    name = newName;

    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    // translations
    zoom = -3.0;
    xPos = newX;
    yPos = newY;

    // Initialize Quad
    vertices[0].x = -width / 2;
    vertices[0].y = -height / 2;
    vertices[0].z = zoom;

    vertices[1].x = width / 2;
    vertices[1].y = -height / 2;
    vertices[1].z = zoom;

    vertices[2].x = width / 2;
    vertices[2].y = height / 2;
    vertices[2].z = zoom;

    vertices[3].x = -width / 2;
    vertices[3].y = height / 2;
    vertices[3].z = zoom;
}

Model::~Model()
{

}
void Model::DrawModel()
{
    //render this model
    glColor3f(1.0, 1.0, 1.0);
    texture->Binder(); // update texture
//    if(this->name != "player")
    glTranslated(this->xPos, this->yPos, this->zoom);
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
}

void Model::InitModel(char* fileName, bool transparent)
{
    if(transparent)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // blends object to background color instead. Change it to mess with cool effects
    }
    texture->Binder();
     cout << "Loading Model: " << fileName << endl;
    texture->BindTexture(fileName);

}

bool Model::Collision(Model* collider)
{
    return Overlapping(xPos - width / 2, xPos + width / 2, collider->GetX() - collider->GetWidth() / 2,
                       collider->GetX() + collider->GetWidth() / 2) &&
           Overlapping(yPos - height / 2, yPos + height / 2, collider->GetY() - collider->GetHeight() / 2,
                       collider->GetY() + collider->GetHeight() / 2);
}

bool Model::Overlapping(double min0, double max0, double min1, double max1)
{
    return max0 >= min1 && min0 <= max1;
}

bool Model::OverlapGround(double maxY, double minY)
{
    return minY == maxY;
}

bool Model::GroundCheck(Model* collider)
{
    return Collision(collider) && OverlapGround(collider->GetY(), yPos + height);
}


double Model::GetX()
{
    return xPos;
}

double Model::GetY()
{
    return yPos;
}

float Model::GetWidth()
{
    return width;
}

float Model::GetHeight()
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

void Model::SetWidth(double newWidth)
{
    width = newWidth;
}
