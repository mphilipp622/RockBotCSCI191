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

    // physics
    gravity = 0.98;
    acceleration = 0.0;
    jump = false;
    slowDown = false;
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
    if(slowDown)
        StopMove();
//   cout <<"" << endl; // WHY? Why does it need something here?
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

void Model::Move(float direction)
{
    xDirection = direction; // set local x direction for use with slow down mechanics later

    if(acceleration < 2.0)
        acceleration += .098;

    xPos += (direction * acceleration) * DeltaTime::GetDeltaTime();
}

void Model::SlowDown()
{
    slowDown = true;
}

void Model::StopMove()
{
    if(acceleration > 0)
        acceleration -= .098;
    else
    {
        slowDown = false; // once acceleration is 0, we no longer need to slow down.
        xDirection = 0;
        acceleration = 0;
    }
    cout << acceleration << endl;
    xPos += (xDirection * acceleration) * DeltaTime::GetDeltaTime();
}
