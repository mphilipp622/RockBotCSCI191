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
    xDirection = 1.0;

    name = newName;
    tag = "RangedEnemy";

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
    ignoreGravity = true;

     // physics
    gravity = 0.98;
    acceleration = 0.0;
    accelRate = 0.05;
    deceleration = 0.2; // rate of deceleration
    maxAcceleration = 2.0;
    gravity = -9.80;
    jumpVelocity = 5.0;
    fallVelocity = 0.0;
    idleFrame = 0;

	frameTimer = new Timer();
    frameTimer->Start();

    moveFrame = 0;
    attackFrame = 0;
    idleFrame = 0;
    jumpFrame = 0;
    dyingFrame = 0;

    ignoreGravity = true;

    sound = new AudioSource(name + "Sound", "Audio/SFX/Laser.wav", xPos, yPos, 1.0, false);

    xPathDistance = 3.0;
    xPatrolCenter = xPos; // set patrol center to the starting position. This could also be changed later if needed
    aggroRadius = 2.0;

    attackSpeed = 1.0;
    attackTimer = new Timer();
    attackTimer->Start();
}

void RangedEnemy::InitEnemy()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    for(int i = 0; i < 10; i++)
//        run[i].BindTexture("Images/Player/player" + std::string::to_string(i) + ".png");


    moveAnim[0].BindTexture("Images/Enemies/Ranged_0000.png");
    moveAnim[1].BindTexture("Images/Enemies/Ranged_0001.png");
    moveAnim[2].BindTexture("Images/Enemies/Ranged_0002.png");
    moveAnim[3].BindTexture("Images/Enemies/Ranged_0000.png");
    moveAnim[4].BindTexture("Images/Enemies/Ranged_0001.png");
    moveAnim[5].BindTexture("Images/Enemies/Ranged_0002.png");

    maxMoveFrame = 6;

    idleAnim[0].BindTexture("Images/Enemies/Ranged_0001.png");
    maxIdleFrame = 1;

    deathAnim[0].BindTexture("Images/Enemies/RangedDie0.png");
    deathAnim[1].BindTexture("Images/Enemies/RangedDie1.png");
    deathAnim[2].BindTexture("Images/Enemies/RangedDie2.png");
    deathAnim[3].BindTexture("Images/Enemies/RangedDie3.png");
    dyingFrame = 0;
    maxDeathFrame = 4;

    attackAnim[0].BindTexture("Images/Enemies/RangedAttack_0000.png");
    attackAnim[1].BindTexture("Images/Enemies/RangedAttack_0001.png");
    maxAttackFrame = 2;
}


/////////////////////////////////
// AI FUNCTIONS
/////////////////////////////////

void RangedEnemy::AIRoutine()
{
    if(!PlayerInRange(aggroRadius))
        Patrol(); // if we haven't detected player, then patrol.
    else
    {
        if(moving)
            StopMove();
        if(attackTimer->GetTicks() > attackSpeed * 1000) // convert to MS using 1000
            ShootProjectile(Player::player->GetX(), Player::player->GetY());
    }
}

void RangedEnemy::Patrol()
{
    if(!moving)
        StartMove(xDirection); // move in the previous direction

    if(xPos >= xPatrolCenter + xPathDistance)
        StartMove(-1.0); // If drone has gone too far right, turn around
    else if(xPos <= xPatrolCenter - xPathDistance)
        StartMove(1.0); // if drone has gone too far left, turn around
}

void RangedEnemy::MoveLeft()
{
    slowDown = false;

    xDirection = -1.0;

    if(acceleration > -maxAcceleration)
        acceleration -= accelRate;

    if(acceleration < -maxAcceleration)
        acceleration = -maxAcceleration;

    prevXPos = xPos;
    xPos -= (xDirection * acceleration) * DeltaTime::GetDeltaTime();

    if(CheckCollision())
    {
        // if drone hits a wall, it should stop, turn around, and patrol again.
        xPos = prevXPos;
        slowDown = false;
        xDirection = -xDirection;
        acceleration = 0;
        StartMove(xDirection);
        return;
    }

    sound->SetPosition(xPos, yPos);
}

void RangedEnemy::MoveRight()
{
    slowDown = false;

    xDirection = 1.0;

    if(acceleration < maxAcceleration)
        acceleration += accelRate;

    if(acceleration > maxAcceleration)
        acceleration = maxAcceleration;

    prevXPos = xPos;
    xPos += (xDirection * acceleration) * DeltaTime::GetDeltaTime();

    if(CheckCollision())
    {
        // if drone hits a wall, it should stop, turn around, and patrol again.
        xPos = prevXPos;
        slowDown = false;
        xDirection = -xDirection;
        acceleration = 0;
        StartMove(xDirection);
        return;
    }

    sound->SetPosition(xPos, yPos);
}

void RangedEnemy::StopMove()
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
            // if drone hits a wall, it should stop, turn around, and patrol again.
            xPos = prevXPos;
            slowDown = false;
            xDirection = -xDirection;
            acceleration = 0;
            StartMove(xDirection);
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
            // if drone hits a wall, it should stop, turn around, and patrol again.
            xPos = prevXPos;
            slowDown = false;
            xDirection = -xDirection;
            acceleration = 0;
            StartMove(xDirection);
            return;
        }

        sound->SetPosition(xPos, yPos);
    }
}


void RangedEnemy::ShootProjectile(double xTarget, double yTarget)
{
    isAttacking = true;

    sound->Play();

    Projectile *newProjectile = new Projectile(xPos, yPos, 0.2, 0.2, 1, 4.0, "DroneProjectile", "EnemyProjectile", xTarget, yTarget); // sends relative mouse pointer location
    vector<string> animations;
    for(int i = 0; i < 4; i++)
        animations.push_back("Images/Projectiles/Bullet" + to_string(i) + ".png");

    newProjectile->InitAnimations(animations);
    SceneManager::GetActiveScene()->movableObjects.push_back(newProjectile);

    attackTimer->Reset();
}



///////////////////////////////////
// COLLISION
///////////////////////////////////

bool RangedEnemy::CheckCollision()
{
    for(auto& model : SceneManager::GetActiveScene()->staticObjects)
    {
        if(Collision(model))
            return true;
    }

    return false;
}

bool RangedEnemy::CheckForwardCollision()
{
//    for(auto& model : SceneManager::GetActiveScene()->staticObjects)
//    {
//        // directions will be - or + 1 and will therefore modify how this calculation happens.
//        double tempX = xPos + (0.5 * xDirection);
//        double tempY = yPos + (0.5 * yDirection);
//
//        if(Collision(model, tempX, tempY))
//            return true;
//
//    }
    return false;
}

bool RangedEnemy::CheckForPit()
{
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

}
