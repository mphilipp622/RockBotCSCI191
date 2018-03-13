#include <Model.h>
#include <TextureLoader.h>
#include <DeltaTime.h>
#include <iostream>
#include <algorithm> // max and min
#include <Player.h>
#include <string>

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
    this->width = newWidth;
    this->height = newHeight;

    this->name = newName;

    this->rotateX = 0;
    this->rotateY = 0;
    this->rotateZ = 0;

    // translations
    this->zoom = -3.0;
    this->xPos = newX;
    this->yPos = newY;

    // Initialize Quad
    this->vertices[0].x = -this->width / 2;
    this->vertices[0].y = -this->height / 2;
    this->vertices[0].z = this->zoom;

    this->vertices[1].x = this->width / 2;
    this->vertices[1].y = -this->height / 2;
    this->vertices[1].z = this->zoom;

    this->vertices[2].x = this->width / 2;
    this->vertices[2].y = this->height / 2;
    this->vertices[2].z = this->zoom;

    this->vertices[3].x = -this->width / 2;
    this->vertices[3].y = this->height / 2;
    this->vertices[3].z = this->zoom;
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
    glRotated(this->rotateX, 1, 0, 0);
    glRotated(this->rotateY, 0, 1, 0);
    glRotated(this->rotateZ, 0, 0, 1);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(this->vertices[0].x, this->vertices[0].y, this->vertices[0].z);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(this->vertices[1].x, this->vertices[1].y, this->vertices[1].z);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(this->vertices[2].x, this->vertices[2].y, this->vertices[2].z);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(this->vertices[3].x, this->vertices[3].y, this->vertices[3].z);

    glEnd();
}

void Model::InitModel(string fileName, bool transparent)
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
    return Overlapping(this->xPos - this->width / 2, this->xPos + this->width / 2, collider->GetX() - collider->GetWidth() / 2,
                       collider->GetX() + collider->GetWidth() / 2) &&
           Overlapping(this->yPos - this->height / 2, this->yPos + this->height / 2, collider->GetY() - collider->GetHeight() / 2,
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
    return this->xPos;
}

double Model::GetY()
{
    return this->yPos;
}

float Model::GetWidth()
{
    return this->width;
}

float Model::GetHeight()
{
    return this->height;
}

string Model::GetName()
{
    return this->name;
}

void Model::SetPosition(double newX, double newY)
{
    this->xPos = newX;
    this->yPos = newY;
}

void Model::SetWidth(double newWidth)
{
   this->width = newWidth;
}
