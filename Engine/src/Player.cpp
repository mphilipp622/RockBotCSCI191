#include <Player.h>
#include <TextureLoader.h>
#include <string>
#include <GLScene.h>
#include <cmath>
#include <Projectile.h>

TextureLoader run[4];
TextureLoader idle[5];
TextureLoader jumpAnim[4];

Player* Player::player; // Global getter for the player object

Player::Player(double newX, double newY)
{
    // Collision
    width = 1.0;
    height = 1.0;

    xPos = newX;
    yPos = newY;
    playerZoom = 0;

    // set previous positions to our starting position
    prevXPos = xPos;
    prevYPos = yPos;

    // Initialize Quad
    vertices[0].x = -width / 2;
    vertices[0].y = -height / 2;
    vertices[0].z = playerZoom;

    vertices[1].x = width / 2;
    vertices[1].y = -height / 2;
    vertices[1].z = playerZoom;

    vertices[2].x = width / 2;
    vertices[2].y = height / 2;
    vertices[2].z = playerZoom;

    vertices[3].x = -width / 2;
    vertices[3].y = height / 2;
    vertices[3].z = playerZoom;

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

    playingChords = false;

    name = "player";

    chord = new AudioSource("PlayerSource", "Audio/Music/", xPos, yPos, 1.0, false);

    // create icons for left and right mouse. They will be placed on the left and right side of our player
    icons = {new Model(0.4, 0.45, xPos - width / 2, yPos, "LeftMouseIcon"), new Model(0.4, 0.45, xPos + width / 2, yPos, "RightMouseIcon")};

	frameTimer = new Timer();
    frameTimer->Start();

    chordTimer = new Timer();
    cooldownTimer = new Timer();
    cooldownTargetTime = 0;
    chordTimingWindow = 2000; // chord timing window is 2 seconds. Might modify this later to fit with BPM
    canPlay = true;

    player = this;
}

Player::~Player()
{
    //dtor
}

void Player::DrawPlayer()
{
    glColor3f(1.0, 1.0, 1.0);

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

    icons[0]->InitModel("Images/HUD/LeftMouse.png", true);
    icons[1]->InitModel("Images/HUD/RightMouse.png", true);

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
        if(frameTimer->GetTicks() > 60)
        {
            idleFrame++;
            idleFrame %= 5;
            frameTimer->Reset();
        }

        idle[idleFrame].Binder();
        DrawPlayer();

        glPopMatrix();
        break;

    case 1:
		// Running

        glPushMatrix();

        glTranslated(xPos, yPos, playerZoom);
//        glTranslated(-0.5, -0.5, -1.0);
        if(frameTimer->GetTicks() > 60)
        {
            moveSpeed++;
            moveSpeed %= 4;
            frameTimer->Reset();
        }

        run[moveSpeed].Binder();
        DrawPlayer();

        glPopMatrix();
        break;
    case 2:
		// Jumping

        glPushMatrix();

        glTranslated(xPos, yPos, playerZoom);
//        glTranslated(-0.5, -0.5, -1.0);
        jumpAnim[0].Binder();
        DrawPlayer();

        glPopMatrix();
        break;
    }
}

void Player::Update()
{
    if(playingChords)
    {
        if(chordTimer->GetTicks() > chordTimingWindow)
        {
            // if user has exceeded their timing window, re-random the input. Might want to punish them and add a cooldown, not sure yet
            PlayChords(false);
            PlayChords(true);
        }

        UpdateIcons();
    }

    if(moving)
    {
        if(xDirection > 0)
            MoveRight();
        else if(xDirection < 0)
            MoveLeft();

        if(!jump)
            Actions(1);
        else
            Actions(2);
    }
    else if(!moving && !jump)
        Actions(0);

    if(jump)
    {
        Jump();
        if(!moving)
            Actions(2);
    }
    else
        ApplyGravity();

    if(slowDown)
        StopMove();

    if(!canPlay)
        UpdateCooldownTimer();
//    DrawPlayer();
}


void Player::StartJump()
{
    if(jump)
        return; // if we're already jumping, don't allow another jump

    jump = true;
    jumpVelocity = 6.0;
    initialY = yPos;
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
    chord->SetPosition(xPos, yPos);
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
    chord->SetPosition(xPos, yPos);
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
    chord->SetPosition(xPos, yPos);
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
    chord->SetPosition(xPos, yPos);
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
        chord->SetPosition(xPos, yPos);
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
        chord->SetPosition(xPos, yPos);
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
    Projectile *newProjectile = new Projectile(xPos, yPos, 0.5, 0.5, 1, 4.0, "projectile", x + xPos, y + yPos); // sends relative mouse pointer location
    newProjectile->InitModel("Images/Note.png", true);
    chord->PlayChord("ab9");
    GLScene::movableObjects.push_back(newProjectile);
}

void Player::UpdateIcons()
{
    icons[0]->SetPosition(xPos - width / 1.5, yPos);
    icons[1]->SetPosition(xPos + width / 1.5, yPos);

    if(playingChords)
        icons[activeInput]->DrawModel();
//    if(playingChords)
//    {
//        for(auto& icon : icons)
//            icon->DrawModel();
//    }
}

void Player::PlayChords(bool isPlaying)
{
    if(!canPlay)
        return;

    playingChords = isPlaying;

    if(playingChords)
    {
        // set the active input user must press and start a timer.
        srand(time(NULL));
        activeInput = rand() % icons.size();

        chordTimer->Start();
    }
    else
        chordTimer->Stop();

}

void Player::CheckUserInput(int userInput)
{
    if(!canPlay)
        // stop execution if waiting for cooldown
        return;

    if(activeInput == userInput)
    {
        cout << "Successful Input" << endl;
    }
    else
    {
        cout << "Failed Input" << endl;
        // set a cooldown for player
        cooldownTimer->Start();
        cooldownTargetTime = chordTimingWindow;
        PlayChords(false);
        canPlay =  false;
    }

}

void Player::UpdateCooldownTimer()
{
    if(cooldownTimer->GetTicks() > cooldownTargetTime)
    {
        canPlay = true;
        cooldownTimer->Stop();
        cooldownTargetTime = 0;
    }
}

