#include <Player.h>
#include <Timer.h>
#include <TextureLoader.h>
#include <string>
#include <GLScene.h>
#include <cmath>
#include <Projectile.h>

Timer *T;
TextureLoader run[4];
TextureLoader idle[5];
TextureLoader jumpAnim[4];

Player* Player::player; // Global getter for the player object

Player::Player(double newX, double newY)
{
    // Collision
    this->width = 1.0;
    this->height = 1.0;

    this->xPos = newX;
    this->yPos = newY;
    this->playerZoom = 0;

    // set previous positions to our starting position
    this->prevXPos = xPos;
    this->prevYPos = yPos;

    // Initialize Quad
    this->vertices[0].x = -this->width / 2;
    this->vertices[0].y = -this->height / 2;
    this->vertices[0].z = this->playerZoom;

    this->vertices[1].x = this->width / 2;
    this->vertices[1].y = -this->height / 2;
    this->vertices[1].z = this->playerZoom;

    this->vertices[2].x = this->width / 2;
    this->vertices[2].y = this->height / 2;
    this->vertices[2].z = this->playerZoom;

    this->vertices[3].x = -this->width / 2;
    this->vertices[3].y = this->height / 2;
    this->vertices[3].z = this->playerZoom;

    this->moveSpeed = 1.0;
    this->jumpSpeed = 1.0;
    this->hp = 3;
    this->actionTrigger = 0;

     // physics
    this->gravity = 0.98;
    this->acceleration = 0.0;
    this->accelRate = 0.05;
    this->deceleration = 0.2; // rate of deceleration
    this->maxAcceleration = 2.5;
    this->jump = false; // set true to avoid falling through earth on scene load
    this->slowDown = false;
    this->gravity = -9.80;
    this->moving = false;
    this->jumpVelocity = 5.0;
    this->fallVelocity = 0.0;
    this->idleFrame = 0;

    this->name = "player";

    this->chord = new AudioSource("PlayerSource", "Audio/Music/", this->xPos, this->yPos, 1.0, false);

	T = new Timer();
    T->Start();

    this->player = this;
}

Player::~Player()
{
    //dtor
}

void Player::DrawPlayer()
{
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

	if (this->xDirection == -1.0)
	{
		// flip texture to the left

		glTexCoord2f(0.0, 1.0);
		glVertex3f(-this->vertices[0].x, this->vertices[0].y, this->vertices[0].z);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(-this->vertices[1].x, this->vertices[1].y, this->vertices[1].z);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(-this->vertices[2].x, this->vertices[2].y, this->vertices[2].z);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(-this->vertices[3].x, this->vertices[3].y, this->vertices[3].z);
	}
	else
	{
		// flip texture to the right

		glTexCoord2f(0.0, 1.0);
		glVertex3f(this->vertices[0].x, this->vertices[0].y, this->vertices[0].z);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(this->vertices[1].x, this->vertices[1].y, this->vertices[1].z);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(this->vertices[2].x, this->vertices[2].y, this->vertices[2].z);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(this->vertices[3].x, this->vertices[3].y, this->vertices[3].z);
	}

    glEnd();

}

void Player::InitPlayer()
{
    // player must always render last in the scene
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    for(int i = 0; i < 10; i++)
//        run[i].BindTexture("Images/Player/player" + std::string::to_string(i) + ".png");
    run[0].BindTexture("Images/Player/Test_Movement_0000.png");
    run[1].BindTexture("Images/Player/Test_Movement_0001.png");
    run[2].BindTexture("Images/Player/Test_Movement_0002.png");
    run[3].BindTexture("Images/Player/Test_Movement_0003.png");

    idle[0].BindTexture("Images/Player/Test_Idle_0000.png");
    idle[1].BindTexture("Images/Player/Test_Idle_0001.png");
    idle[2].BindTexture("Images/Player/Test_Idle_0002.png");
    idle[3].BindTexture("Images/Player/Test_Idle_0003.png");
    idle[4].BindTexture("Images/Player/Test_Idle_0004.png");

    jumpAnim[0].BindTexture("Images/Player/Test_Movement_0000.png");
    jumpAnim[1].BindTexture("Images/Player/Test_Movement_0001.png");
    jumpAnim[2].BindTexture("Images/Player/Test_Movement_0002.png");
    jumpAnim[3].BindTexture("Images/Player/Test_Movement_0003.png");

}

void Player::Actions(int newAction)
{
    switch(newAction)
    {
    case 0:
		// Idle

        glPushMatrix();

        glTranslated(xPos, yPos, playerZoom);
//        glTranslated(-0.5, -0.5, -1.0);
        if(T->GetTicks() > 60)
        {
            this->idleFrame++;
            this->idleFrame %= 5;
            T->Reset();
        }

        idle[this->idleFrame].Binder();
        this->DrawPlayer();

        glPopMatrix();
        break;

    case 1:
		// Running

        glPushMatrix();

        glTranslated(xPos, yPos, playerZoom);
//        glTranslated(-0.5, -0.5, -1.0);
        if(T->GetTicks() > 60)
        {
            this->moveSpeed++;
            this->moveSpeed %= 4;
            T->Reset();
        }

        run[this->moveSpeed].Binder();
        this->DrawPlayer();

        glPopMatrix();
        break;
    case 2:
		// Jumping

        glPushMatrix();

        glTranslated(xPos, yPos, playerZoom);
//        glTranslated(-0.5, -0.5, -1.0);
        jumpAnim[0].Binder();
        this->DrawPlayer();

        glPopMatrix();
        break;
    }
}

void Player::Update()
{
    if(this->moving)
    {
        if(this->xDirection > 0)
            this->MoveRight();
        else if(xDirection < 0)
            this->MoveLeft();

        if(!this->jump)
            this->Actions(1);
        else
            this->Actions(2);
    }
    else if(!this->moving && !this->jump)
        this->Actions(0);

    if(this->jump)
    {
        this->Jump();
        if(!this->moving)
            this->Actions(2);
    }
    else
        this->ApplyGravity();

    if(this->slowDown)
        this->StopMove();


//    DrawPlayer();
}


void Player::StartJump()
{
    if(this->jump)
        return; // if we're already jumping, don't allow another jump

    this->jump = true;
    this->jumpVelocity = 6.0;
    this->initialY = yPos;
}

void Player::Jump()
{
    // Will probably move this into a player class later

    jumpVelocity += gravity * DeltaTime::GetDeltaTime();
    prevYPos = yPos;
    yPos += jumpVelocity * DeltaTime::GetDeltaTime();
    if(CheckCollision())
    {
//        GLScene::keyboardAndMouse->SetKey("Jump", false);
        jump = false;
        yPos = prevYPos;
        return;
    }
    AudioEngine::SetPosition(xPos, yPos);
    this->chord->SetPosition(this->xPos, this->yPos);
    GLScene::UpdateModelPositions();
}

void Player::ApplyGravity()
{
//    jumpVelocity += gravity * DeltaTime::GetDeltaTime();

    if(DeltaTime::GetDeltaTime() > 1)
        return; // kill if delta time is too high

    fallVelocity += gravity * DeltaTime::GetDeltaTime();

    if(fallVelocity < sqrt(2 * gravity))
        fallVelocity =  sqrt(2 * gravity); // set to terminal velocity

    prevYPos = yPos;
    yPos += fallVelocity * DeltaTime::GetDeltaTime();

    if(CheckCollision())
    {
        fallVelocity = 0;
        yPos = prevYPos;
        return;
    }
    AudioEngine::SetPosition(xPos, yPos);
    this->chord->SetPosition(this->xPos, this->yPos);
    GLScene::UpdateModelPositions();
}

void Player::StartMove(float dir)
{
    xDirection = dir;
    moving = true;
}

void Player::MoveLeft()
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
//        GLScene::keyboardAndMouse->SetKey("MoveLeft", false);
        xPos = prevXPos;
        moving = false;
        xDirection = 0;
        acceleration = 0;
        return;
    }
    AudioEngine::SetPosition(xPos, yPos);
    this->chord->SetPosition(this->xPos, this->yPos);
    GLScene::UpdateModelPositions();
}

void Player::MoveRight()
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

//        GLScene::keyboardAndMouse->SetKey("MoveRight", false);
        xPos = prevXPos;
        moving = false;
        xDirection = 0;
        acceleration = 0;
        return;
    }
    AudioEngine::SetPosition(xPos, yPos);
    this->chord->SetPosition(this->xPos, this->yPos);
    GLScene::UpdateModelPositions();

}

void Player::SlowDown()
{
    prevXDirection = xDirection;
    slowDown = true;
    moving = false;
}

void Player::StopMove()
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
            moving = false;
            slowDown = false;
            xDirection = 0;
            acceleration = 0;
            return;
        }
        AudioEngine::SetPosition(xPos, yPos);
        this->chord->SetPosition(this->xPos, this->yPos);
        GLScene::UpdateModelPositions();

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
            moving = false;
            slowDown = false;
            xDirection = 0;
            acceleration = 0;
            return;
        }
        AudioEngine::SetPosition(xPos, yPos);
        this->chord->SetPosition(this->xPos, this->yPos);
        GLScene::UpdateModelPositions();
    }

}

bool Player::CheckCollision()
{

    for(auto& model : GLScene::staticObjects)
    {
        if(Collision(model))
            return true;

    }

    return false;
}

double Player::GetOffsetX()
{
    return xPos - prevXPos;
}

double Player::GetOffsetY()
{
    return yPos - prevYPos;
}

double Player::GetZoom()
{
    return playerZoom;
}

void Player::ShootProjectile(double x, double y)
{
    Projectile *newProjectile = new Projectile(this->xPos, this->yPos, 0.5, 0.5, 1, 4.0, "projectile", x + this->xPos, y + this->yPos); // sends relative mouse pointer location
    newProjectile->InitModel("Images/Note.png", true);
    chord->PlayChord("ab9");
    GLScene::movableObjects.push_back(newProjectile);
}
