#include "MeleeEnemy.h"

MeleeEnemy::MeleeEnemy()
{
    //ctor
}

MeleeEnemy::~MeleeEnemy()
{
    //dtor
}

MeleeEnemy::MeleeEnemy(double newX, double newY, double newWidth, double newHeight, string newName)
{
    xPos = newX;
    yPos = newY;
    width = newWidth;
    height = newHeight;
    zoom = 0;

    name = newName;
    tag = "MeleeEnemy";

    // set previous positions to our starting position
    prevXPos = xPos;
    prevYPos = yPos;

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

    moveSpeed = 1.0;
    jumpSpeed = 1.0;
    hp = 3;
    actionTrigger = 0;
    isDying = false;

     // physics
    gravity = 0.98;
    acceleration = 0.0;
    accelRate = 0.05;
    deceleration = 0.2; // rate of deceleration
    maxAcceleration = 2.0;
    jump = false; // set true to avoid falling through earth on scene load
    slowDown = false;
    gravity = -9.80;
    moving = false;
    jumpVelocity = 5.0;
    fallVelocity = 0.0;
    idleFrame = 0;

	frameTimer = new Timer();
    frameTimer->Start();

    sound = new AudioSource(name + "Sound", "", xPos, yPos, 1.0, false);

    aggroRadius = 3;
}

void MeleeEnemy::InitEnemy()
{
    // player must always render last in the scene
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    for(int i = 0; i < 10; i++)
//        run[i].BindTexture("Images/Player/player" + std::string::to_string(i) + ".png");


    moveAnim[0].BindTexture("Images/Enemies/Melee0.png");
    moveAnim[1].BindTexture("Images/Enemies/Melee1.png");
    moveAnim[2].BindTexture("Images/Enemies/Melee2.png");
    moveAnim[3].BindTexture("Images/Enemies/Melee3.png");

    maxMoveFrame = 4;

    idleAnim[0].BindTexture("Images/Enemies/MeleeIdle.png");
    maxIdleFrame = 1;

    jumpAnim[0].BindTexture("Images/Enemies/MeleeJump.png");
    maxJumpFrame = 1;

}

bool MeleeEnemy::CheckCollision()
{
    for(auto& model : SceneManager::GetActiveScene()->staticObjects)
    {
        if(Collision(model))
            return true;
    }

    return false;
}

bool MeleeEnemy::CheckCircleCollision()
{
    return false;
}

bool MeleeEnemy::CheckCircleSquareCollision()
{
    return false;
}

bool MeleeEnemy::CheckForwardCollision()
{
    for(auto& model : SceneManager::GetActiveScene()->staticObjects)
    {
        // directions will be - or + 1 and will therefore modify how this calculation happens.
        double tempX = xPos + (0.5 * xDirection);
        double tempY = yPos + (0.5 * yDirection);

        for(auto& model : SceneManager::GetActiveScene()->staticObjects)
        {
            if(Collision(model, tempX, tempY))
                return true;
        }

        return false;
    }
}


void MeleeEnemy::AIRoutine()
{
    // check if player is in aggro radius. If not, then enemy should stop if they're moving and stop the AI routine.
    if(!AggroOverlap())
    {
        if(moving)
            StopMove();

        return;
    }

    if(Player::player->GetX() < xPos)
        StartMove(-1.0); // move left
    else if(Player::player->GetX() > xPos)
        StartMove(1.0);
}
