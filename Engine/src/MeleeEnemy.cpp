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
    isAttacking = false;
    jump = false;
    moving = false;
    slowDown = false;
    ignoreGravity = false;

     // physics
    gravity = 0.98;
    acceleration = 0.0;
    accelRate = 0.05;
    deceleration = 0.2; // rate of deceleration
    maxAcceleration = 1.5;
    gravity = -9.80;
    jumpVelocity = 5.0;
    fallVelocity = 0.0;
    idleFrame = 0;

	frameTimer = new Timer();
    frameTimer->Start();

    moveFrame = 0;
    jumpFrame = 0;
    attackFrame = 0;
    idleFrame = 0;
    dyingFrame = 0;

    sound = new AudioSource(name + "Sound", "", xPos, yPos, 1.0, false);

    aggroRadius = 3;
    meleeRange = 0.5;
}

void MeleeEnemy::InitEnemy()
{
    // player must always render last in the scene
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    for(int i = 0; i < 10; i++)
//        run[i].BindTexture("Images/Player/player" + std::string::to_string(i) + ".png");


    moveAnim[0].BindTexture("Images/Enemies/Melee_0000.png");
    moveAnim[1].BindTexture("Images/Enemies/Melee_0001.png");
    moveAnim[2].BindTexture("Images/Enemies/Melee_0002.png");
    moveAnim[3].BindTexture("Images/Enemies/Melee_0003.png");
    moveAnim[4].BindTexture("Images/Enemies/Melee_0000.png");
    moveAnim[5].BindTexture("Images/Enemies/Melee_0001.png");
    moveAnim[6].BindTexture("Images/Enemies/Melee_0002.png");

    maxMoveFrame = 7;

    idleAnim[0].BindTexture("Images/Enemies/Melee_0000.png");
    idleAnim[1].BindTexture("Images/Enemies/Melee_0001.png");
    idleAnim[2].BindTexture("Images/Enemies/Melee_0002.png");
    idleAnim[3].BindTexture("Images/Enemies/Melee_0003.png");
    idleAnim[4].BindTexture("Images/Enemies/Melee_0000.png");

    maxIdleFrame = 5;

    jumpAnim[0].BindTexture("Images/Enemies/Melee_0000.png");
    jumpAnim[1].BindTexture("Images/Enemies/Melee_0001.png");
    maxJumpFrame = 2;

    deathAnim[0].BindTexture("Images/Enemies/Melee_0000.png");
    maxDeathFrame = 1;

    attackAnim[0].BindTexture("Images/Enemies/MeleeAttack_0000.png");
    attackAnim[1].BindTexture("Images/Enemies/MeleeAttack_0001.png");
    attackAnim[2].BindTexture("Images/Enemies/MeleeAttack_0002.png");
    attackAnim[3].BindTexture("Images/Enemies/MeleeAttack_0003.png");
    maxAttackFrame = 4;

}

void MeleeEnemy::MoveLeft()
{
    slowDown = false;

    xDirection = -1.0;

    if(acceleration > -maxAcceleration)
        acceleration -= accelRate;

    if(acceleration < -maxAcceleration)
        acceleration = -maxAcceleration;

    prevXPos = xPos;
    xPos -= (xDirection * acceleration) * DeltaTime::GetDeltaTime();

    if(!falling && CheckForPit() && Player::player->GetY() >= yPos)
    {
        // If a pit is ahead of us, and player is at enemy's y position or greater, then jump
        StartJump();
    }

    if(CheckCollision())
    {
        jump = true;
        xPos = prevXPos;
        xDirection = 0;
        acceleration = 0;
        return;
    }

    if(CheckForwardCollision() && !falling)
        StartJump();

    sound->SetPosition(xPos, yPos);
}

void MeleeEnemy::MoveRight()
{
    slowDown = false;

    xDirection = 1.0;

    if(acceleration < maxAcceleration)
        acceleration += accelRate;

    if(acceleration > maxAcceleration)
        acceleration = maxAcceleration;

    prevXPos = xPos;
    xPos += (xDirection * acceleration) * DeltaTime::GetDeltaTime();

    if(!falling && CheckForPit() && Player::player->GetY() >= yPos)
    {
        // If a pit is ahead of us, and player is at enemy's y position or greater, then jump
        StartJump();
    }

    if(CheckCollision())
    {
        jump = true;
        xPos = prevXPos;
        xDirection = 0;
        acceleration = 0;
        return;
    }

    if(CheckForwardCollision() && !falling)
        StartJump();

    sound->SetPosition(xPos, yPos);
}


void MeleeEnemy::StopMove()
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

        prevXPos = xPos;
        xPos += (prevXDirection * acceleration) * DeltaTime::GetDeltaTime();

        if(CheckCollision())
        {
            xPos = prevXPos;
            slowDown = false;
            xDirection = 0;
            acceleration = 0;
            return;
        }
        sound->SetPosition(xPos, yPos);

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

        prevXPos = xPos;
        xPos -= (prevXDirection * acceleration) * DeltaTime::GetDeltaTime();

        if(CheckCollision())
        {
            xPos = prevXPos;
            slowDown = false;
            xDirection = 0;
            acceleration = 0;
            return;
        }
        sound->SetPosition(xPos, yPos);
    }
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

        if(Collision(model, tempX, tempY))
            return true;


    }

    return false;
}

bool MeleeEnemy::CheckForPit()
{
    for(auto& model : SceneManager::GetActiveScene()->staticObjects)
    {
        // directions will be - or + 1 and will therefore modify how this calculation happens.
        double tempX = xPos + (0.3 * xDirection);
        double tempY = yPos - 0.1;

        if(Collision(model, tempX, tempY))
            return false;


    }
    return true;
}


void MeleeEnemy::AIRoutine()
{
    // check if player is in aggro radius. If not, then enemy should stop if they're moving and stop the AI routine.
    if(!PlayerInRange(aggroRadius))
    {
        if(moving)
            StopMove();

        return;
    }

    if(PlayerInRange(meleeRange))
    {
        slowDown = true;
        isAttacking = true;
        return;
    }
    else
    {
        isAttacking = false;
        slowDown = false;
    }


    if(Player::player->GetX() < xPos)
        StartMove(-1.0); // move left
    else if(Player::player->GetX() > xPos)
        StartMove(1.0);
}
