#include "Enemy.h"
#include <GLScene.h>

Enemy::Enemy()
{
    //ctor
}

Enemy::Enemy(double newX, double newY, double newWidth, double newHeight, string newName, string newTag)
{
    xPos = newX;
    yPos = newY;
    width = newWidth;
    height = newHeight;
    zoom = 0;

    name = newName;
    tag = newTag;

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

     // physics
    gravity = 0.98;
    acceleration = 0.0;
    accelRate = 0.05;
    deceleration = 0.2; // rate of deceleration
    maxAcceleration = 2.5;
    jump = false; // set true to avoid falling through earth on scene load
    slowDown = false;
    gravity = -9.80;
    moving = false;
    jumpVelocity = 5.0;
    fallVelocity = 0.0;
    idleFrame = 0;

	frameTimer = new Timer();
    frameTimer->Start();

    isDying = false;
    ignoreGravity = false;
    falling = false;

    isAttacking = false;

    sound = new AudioSource(name + "Sound", "", xPos, yPos, 1.0, false);
}


Enemy::~Enemy()
{
    //dtor
}


void Enemy::DrawEnemy()
{
    glColor4f(1.0, 1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

	if (xDirection == -1.0)
	{
		// flip texture to the left

		glTexCoord2f(0.0, 1.0);
		glVertex3f(-vertices[0].x, vertices[0].y, vertices[0].z);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(-vertices[1].x, vertices[1].y, vertices[1].z);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(-vertices[2].x, vertices[2].y, vertices[2].z);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(-vertices[3].x, vertices[3].y, vertices[3].z);
	}
	else
	{
		// flip texture to the right

		glTexCoord2f(0.0, 1.0);
		glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	}

    glEnd();
}


void Enemy::Update()
{
    if(isDying)
    {
        Actions(3);
        return;
    }

    if(moving)
    {
        if(xDirection > 0)
            MoveRight();
        else if(xDirection < 0)
            MoveLeft();

        if(!jump && !isAttacking)
            Actions(1);
        else if(jump && !isAttacking)
            Actions(2);
    }
    else if(!moving && !jump && !isAttacking)
        Actions(0);

    if(jump)
    {
        Jump();
        if(!moving && !isAttacking)
            Actions(2);
    }
    else
        ApplyGravity();

    if(slowDown)
        StopMove();

    if(isAttacking)
        Actions(4);

    AIRoutine();
}

void Enemy::TakeDamage(int damageTaken)
{
    hp -= damageTaken;

    if(hp <= 0)
        isDying = true; // start the dying process.
}

void Enemy::StartMove(float dir)
{
    xDirection = dir;
    moving = true;
}

void Enemy::SlowDown()
{
    prevXDirection = xDirection;
    slowDown = true;
    moving = false;
}

void Enemy::ApplyGravity()
{
    if(ignoreGravity)
        return;

    if(DeltaTime::GetDeltaTime() > 0.2)
        return; // kill if delta time is too high

    falling = true;
    fallVelocity += gravity * DeltaTime::GetDeltaTime();

    if(fallVelocity < sqrt(2 * gravity))
        fallVelocity =  sqrt(2 * gravity); // set to terminal velocity

    prevYPos = yPos;
    yPos += fallVelocity * DeltaTime::GetDeltaTime();

    // Check Pit Collision

    if(CheckCollision())
    {
        if(CheckForPit() && Player::player->GetY() >= yPos)
        {
            cout << " JUMP " << endl;
            // If a pit is ahead of us, and player is at enemy's y position or greater, then jump
            StartJump();
        }


        fallVelocity = 0;
        yPos = prevYPos;
        falling = false;
        return;
    }

    sound->SetPosition(xPos, yPos);
}

void Enemy::Jump()
{
    jumpVelocity += gravity * DeltaTime::GetDeltaTime();
    prevYPos = yPos;
    yPos += jumpVelocity * DeltaTime::GetDeltaTime();

    if(CheckCollision())
    {
        jump = false;
        yPos = prevYPos;
        return;
    }
    sound->SetPosition(xPos, yPos);
}

void Enemy::StartJump()
{
    if(jump)
        return; // if we're already jumping, don't allow another jump

    jump = true;
    jumpVelocity = 6.0;
    initialY = yPos;
}

void Enemy::Die()
{
    auto finder = find(SceneManager::GetActiveScene()->enemies.begin(), SceneManager::GetActiveScene()->enemies.end(), this);
    SceneManager::GetActiveScene()->enemies.erase(finder);
    delete this;
}

void Enemy::Actions(int newAction)
{
    glEnable(GL_TEXTURE_2D);
    switch(newAction)
    {
    case 0:
		// Idle

        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            idleFrame++;
            idleFrame %= maxIdleFrame;
            frameTimer->Reset();
        }

        idleAnim[idleFrame].Binder();
        DrawEnemy();

        glPopMatrix();
        break;

    case 1:
		// Running

        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            moveFrame++;
            moveFrame %= maxMoveFrame;
            frameTimer->Reset();
        }

        moveAnim[moveFrame].Binder();
        DrawEnemy();

        glPopMatrix();
        break;
    case 2:
		// Jumping

        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            jumpFrame++;
            jumpFrame %= maxJumpFrame;
            frameTimer->Reset();
        }

        jumpAnim[jumpFrame].Binder();
        DrawEnemy();

        glPopMatrix();
        break;

    case 3:
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            dyingFrame++;
            dyingFrame %= maxDeathFrame;
            frameTimer->Reset();
        }

        deathAnim[dyingFrame].Binder();
        DrawEnemy();

        glPopMatrix();

        if(dyingFrame == 0)
            // animation is over. Delete from game
            Die();
        break;
    case 4:
        cout << "ATTACKING " << endl;
        glPushMatrix();

        glTranslated(xPos, yPos, zoom);

        if(frameTimer->GetTicks() > 60)
        {
            attackFrame++;
            attackFrame %= maxAttackFrame;

            if(attackFrame == 0) // only show the attack animation one time before stopping.
                isAttacking = false;

            frameTimer->Reset();
        }

        attackAnim[attackFrame].Binder();
        DrawEnemy();

        glPopMatrix();

        break;
    }
    glDisable(GL_TEXTURE_2D);
}

bool Enemy::PlayerInRange(double checkRadius)
{
    return OverlappingCircles(xPos, yPos, Player::player->GetX(), Player::player->GetY(), checkRadius, Player::player->GetRadius());

}
