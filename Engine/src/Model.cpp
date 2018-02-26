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
    zoom = -8.0;
    xPos = 0;
    yPos = 0;

    // physics
    gravity = 0.98;
    acceleration = 0.0;
    jump = false;
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


    //Uncomment the below to make teapot object
    //glScalef(1.0, 1.0, 0.0);
    //glutSolidTeapot(1.0);

    //This draws out a perfect 2D square.
    glBegin(GL_POLYGON);
    glVertex3f(-0.500000, -0.500000, 0.500000);
    glVertex3f(0.500000, -0.500000, 0.500000);
    glVertex3f(0.500000, 0.500000, 0.500000);
    glVertex3f(-0.500000, 0.500000, 0.500000);
    glEnd();
}

void Model::InitModel(char* fileName)
{
    texture->Binder();
     cout << "Loading Model: " << fileName << endl;
    texture->BindTexture(fileName);

}

void Model::Jump()
{
    // Will probably move this into a player class later
    if(yPos < jumpY)
        yPos += 1 * DeltaTime::GetDeltaTime();
    else if(yPos > initialY)
    {
        yPos -= 1 * DeltaTime::GetDeltaTime();
        jumpY = initialY; // reset this so we fall. Will replace with physics later.
    }
    else
        jump = false;
}


void Model::NormalAttack(bool newVal)
{
    if(newVal)
    {
        cout << "attacking" << endl;
    }

}

void Model::Update()
{
    if(jump)
        Jump();

   cout <<"" << endl; // WHY? Why does it need something here?
}

void Model::SetJump(bool newVal)
{
    jump = newVal;
    if(jump)
    {
        jumpY = yPos + 2.0;
        initialY = yPos;
    }
}
