#include "RangedEnemy.h"

RangedEnemy::RangedEnemy()
{

}

RangedEnemy::RangedEnemy(double newX, double newY, double newWidth, double newHeight, string newName)
{
    xPos = newX;
    yPos = newY;
    width = newWidth;
    height = newHeight;
    zoom = 0;

    name = newName;
    tag = "Enemy";

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
}

void RangedEnemy::InitEnemy()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    for(int i = 0; i < 10; i++)
//        run[i].BindTexture("Images/Player/player" + std::string::to_string(i) + ".png");


    moveAnim[0].BindTexture("Images/Enemies/RangedWalk0.png");
    moveAnim[1].BindTexture("Images/Enemies/RangedWalk1.png");
    moveAnim[2].BindTexture("Images/Enemies/RangedWalk2.png");
    moveAnim[3].BindTexture("Images/Enemies/RangedWalk3.png");
    moveAnim[4].BindTexture("Images/Enemies/RangedWalk4.png");
    moveAnim[5].BindTexture("Images/Enemies/RangedWalk5.png");

    maxMoveFrame = 6;

    idleAnim[0].BindTexture("Images/Enemies/RangedIdle0.png");
    maxIdleFrame = 1;

    deathAnim[0].BindTexture("Images/Enemies/RangedDie0.png");
    deathAnim[1].BindTexture("Images/Enemies/RangedDie1.png");
    deathAnim[2].BindTexture("Images/Enemies/RangedDie2.png");
    deathAnim[3].BindTexture("Images/Enemies/RangedDie3.png");
    dyingFrame = 0;
    maxDeathFrame = 4;

    attackAnim[0].BindTexture("Images/Enemies/RangedIdle0.png");
    attackAnim[1].BindTexture("Images/Enemies/RangedIdle1.png");
    attackAnim[2].BindTexture("Images/Enemies/RangedIdle2.png");
    maxAttackFrame = 3;
}

void RangedEnemy::AIRoutine()
{
//    if(Player::player->GetX() < xPos)
//        StartMove(-1.0); // move left
//    else if(Player::player->GetX() > xPos)
//        StartMove(1.0);
}

bool RangedEnemy::CheckCollision()
{
    for(auto& model : SceneManager::GetActiveScene()->staticObjects)
    {
        if(Collision(model))
            return true;
    }

    return false;
}

bool RangedEnemy::CheckCircleCollision()
{
    return false;
}

bool RangedEnemy::CheckCircleSquareCollision()
{
    return false;
}


RangedEnemy::~RangedEnemy()
{
    //dtor
}
