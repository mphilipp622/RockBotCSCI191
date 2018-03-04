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
    accelRate = 0.05;
    deceleration = 0.2; // rate of deceleration
    maxAcceleration = 2.0;
    jump = false;
    slowDown = false;
    gravity = -9.80;
    moving = false;
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

void Model::Update()
{
    if(moving)
    {
        if(xDirection > 0)
            MoveRight();
        else if(xDirection < 0)
            MoveLeft();
    }
    if(jump)
        Jump();
    if(slowDown)
        StopMove();
//   cout <<"" << endl; // WHY? Why does it need something here?
}

void Model::NormalAttack(bool newVal)
{
    if(newVal)
    {
        cout << "attacking" << endl;
    }

}

void Model::StartJump()
{
    if(jump)
        return; // if we're already jumping, don't allow another jump

    jump = true;
    jumpVelocity = 4.0;
    initialY = yPos;
}

void Model::Jump()
{
    // Will probably move this into a player class later
//    if(yPos < jumpY)
    jumpVelocity += gravity * DeltaTime::GetDeltaTime();
    yPos += jumpVelocity * DeltaTime::GetDeltaTime();
    if(yPos <= initialY)
    {
        yPos = initialY;
        jump = false;
    }
//    else if(yPos > initialY)
//    {
//        yPos -= 1.0 * DeltaTime::GetDeltaTime();
//        jumpY = initialY; // reset this so we fall. Will replace with physics later.
//    }
//    else
//        jump = false;
}

void Model::StartMove(float dir)
{
    xDirection = dir;
    moving = true;
}

void Model::MoveLeft()
{
    slowDown = false;

    xDirection = -1.0;

    if(acceleration > -maxAcceleration)
        acceleration -= accelRate;

    if(acceleration < -maxAcceleration)
        acceleration = -maxAcceleration;

    xPos -= (xDirection * acceleration) * DeltaTime::GetDeltaTime();
}

void Model::MoveRight()
{
    slowDown = false;

    xDirection = 1.0;

    if(acceleration < maxAcceleration)
        acceleration += accelRate;

    if(acceleration > maxAcceleration)
        acceleration = maxAcceleration;

    xPos += (xDirection * acceleration) * DeltaTime::GetDeltaTime();
}

void Model::SlowDown()
{
    prevXDirection = xDirection;
    slowDown = true;
    moving = false;
}

void Model::StopMove()
{
    moving = false;
    if(prevXDirection > 0)
    {
        // if we're moving right, execute different code

        if(acceleration > 0)
            acceleration -= deceleration;
        else
        {
            slowDown = false; // once acceleration is 0, we no longer need to slow down.
            acceleration = 0; // acceleration is back to baseline
        }

        xPos += (prevXDirection * acceleration) * DeltaTime::GetDeltaTime();
    }
    else if(prevXDirection < 0)
    {
        // Code for left direction slow down

        if(acceleration < 0)
            acceleration += deceleration;
        else
        {
            slowDown = false; // once acceleration is 0, we no longer need to slow down.
            acceleration = 0; // acceleration is back to baseline
        }

        xPos -= (prevXDirection * acceleration) * DeltaTime::GetDeltaTime();
    }

}
