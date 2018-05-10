#include <Player.h>
#include <TextureLoader.h>
#include <string>
#include <GLScene.h>
#include <cmath>
#include <Projectile.h>

Player* Player::player; // Global getter for the player object

Player::Player(double newX, double newY)
{
    // Collision
    width = 1.0;
    height = 1.0;
    radius = width / 2;

    xPos = newX;
    yPos = newY;
    playerZoom = 0;

    // test
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
    hp = 10;
    actionTrigger = 0;
    attackFrame = 0;
    dieFrame = 0;

     // physics
    gravity = 0.98;
    acceleration = 0.0;
    accelRate = 0.2;
    deceleration = 0.2; // rate of deceleration
    maxAcceleration = 3.0;
    pushAccel = 8.0; // used for push back
    pushDecel = 0.6;
    jump = false; // set true to avoid falling through earth on scene load
    slowDown = false;
    gravity = -9.80;
    moving = false;
    attacking = false;
    pushBack = false;
    falling = false;
    isDead = false;
    jumpVelocity = 5.0;
    fallVelocity = 0.0;
    idleFrame = 0;

    xDirection = 1.0;
    prevXDirection = 1.0;

    playingChords = false;
    chordDamage = 1;

    name = "player";
    tag = "Player";

    chord = new AudioSource("PlayerSource", "Audio/Music/Chords/E.ogg", xPos, yPos, 0.8, false);

    // create icons for left and right mouse. They will be placed on the left and right side of our player
    icons =
    {
        new Model(0.4, 0.45, xPos - width / 2, yPos, "LeftMouseIcon", "HUD"),
        new Model(0.4, 0.45, xPos + width / 2, yPos, "RightMouseIcon", "HUD")
    };

    inputIcon = new Model(0.4, 0.45, xPos, yPos + height / 2, "Icon", "Icon");
	frameTimer = new Timer();
    frameTimer->Start();

    chordTimer = new Timer();
    cooldownTimer = new Timer();
    cooldownTargetTime = 0;
    bpm = 120;
    beatsPerInput = 4;

    // Chord Timing Window follows the below equation. the constant 60 is for 60 seconds. 1000 is for converting to ms
    chordTimingWindow = (beatsPerInput / (bpm / 60.0)) * 1000;

    canPlay = true;
    chordManager = new ChordManager();

    invincible = false;
    invincibleTime = 1.0; // player can be invincible for 1 second.
    invincibleTimer = new Timer();
    invincibleFrameTimer = new Timer();

    drawCircle = false;
    musicCircle = new Model(3, 3, xPos, yPos, "MusicCircle", "MusicHUD");
    circleTimer = new Timer();
    fallTimer = new Timer();

    iconNames =
    {
        { 0, "Images/HUD/XButton.png"},
        { 1, "Images/HUD/BButton.png"}
    };

    if(player)
        delete player;

    player = this;

//    PlayChords(true);

    test1_font.init("BADABB__.TTF", 26);
    displayText = false;

    chordTimer->Start();
}

Player::~Player()
{
    //dtor
}

void Player::DrawPlayer()
{
//    glRotated(45.0, 0, 0, -1.0);
//    glPushMatrix();
    if(invincible)
    {
        // Change the player's alpha transparency to make him flicker.
        if(invincibleFrameTimer->GetTicks() > 100)
        {
            invincibleFrame += 1;
            invincibleFrame %= 2;
            glColor4f(1.0, 1.0, 1.0, invincibleFrame); // if the player is invincible from taking damage, color him red
            invincibleFrameTimer->Reset();
        }
        else
            glColor4f(1.0, 1.0, 1.0, invincibleFrame);
    }

    else
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
//    glPopMatrix();
}

void Player::InitPlayer()
{
    // player must always render last in the scene
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    for(int i = 0; i < 10; i++)
//        run[i].BindTexture("Images/Player/player" + std::string::to_string(i) + ".png");
    run[0].BindTexture("Images/Player/Movement_0000.png");
    run[1].BindTexture("Images/Player/Movement_0001.png");
    run[2].BindTexture("Images/Player/Movement_0002.png");
    run[3].BindTexture("Images/Player/Movement_0003.png");

    idle[0].BindTexture("Images/Player/Idle_0000.png");
    idle[1].BindTexture("Images/Player/Idle_0001.png");
    idle[2].BindTexture("Images/Player/Idle_0002.png");
    idle[3].BindTexture("Images/Player/Idle_0003.png");
    idle[4].BindTexture("Images/Player/Idle_0001.png");

    jumpAnim[0].BindTexture("Images/Player/Movement_0000.png");
    jumpAnim[1].BindTexture("Images/Player/Movement_0001.png");
    jumpAnim[2].BindTexture("Images/Player/Movement_0002.png");
    jumpAnim[3].BindTexture("Images/Player/Movement_0003.png");

    attackAnim[0].BindTexture("Images/Player/Attack_0000.png");
    attackAnim[1].BindTexture("Images/Player/Attack_0001.png");
    attackAnim[2].BindTexture("Images/Player/Attack_0002.png");
    attackAnim[3].BindTexture("Images/Player/Attack_0003.png");

    icons[0]->InitModel("Images/HUD/XButton.png", true);
    icons[1]->InitModel("Images/HUD/BButton.png", true);

//    musicCircle->InitModel("Images/MusicSprites/MusicCircle.png", true);

}

void Player::Actions(int newAction)
{

glEnable(GL_TEXTURE_2D);
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
    case 3:
        // Attacking

        glPushMatrix();

        glTranslated(xPos, yPos, playerZoom);

        if(frameTimer->GetTicks() > 60)
        {
            attackFrame++;
            attackFrame %= 4;

            if(attackFrame == 0) // only show the attack animation one time before stopping.
                attacking = false;

            frameTimer->Reset();
        }

        attackAnim[attackFrame].Binder();
        DrawPlayer();

        glPopMatrix();

        break;

    }
    glDisable(GL_TEXTURE_2D);
}

void Player::Update()
{
    if(invincible)
        // check if timer has expired for invincibility.
        CheckInvincible();

    if(playingChords)
    {

        if(chordTimer->GetTicks() > chordTimingWindow)
            // if user has exceeded their timing window, re-random the input. Might want to punish them and add a cooldown, not sure yet
            NextInput();

        UpdateIcons();
    }

    if(moving && !pushBack)
    {

        if(xDirection > 0)
            MoveRight();
        else if(xDirection < 0)
            MoveLeft();

        if(!attacking)
            Actions(1);
//        else if(jump && !attacking)
//            Actions(2);

    }
    else if(!moving && !jump && !attacking)
        Actions(0);

    if(jump)
    {
        Jump();
        if(!moving && !attacking)
            Actions(2);
    }
    else
        ApplyGravity();

    if(slowDown && !pushBack)
        StopMove();

    if(pushBack)
        PushBack();

    if(attacking)
        Actions(3);

    CheckEnemyCollision();

    if(!canPlay)
        UpdateCooldownTimer();

    //////////////
    // DRAW SPARKS
    //////////////

    for(auto& spark : sparks)
    {
        // iterate over all the sparks and update and draw them
        spark->LifetimeSparks();
        spark->DrawSparks();

        if(spark->GetIsDead())
        {
            // if the spark timer has run out, destroy it
//            auto finder = find(sparks.begin(), sparks.end(), spark);
//            sparks.erase(finder);
            sparks.erase(std::remove(sparks.begin(), sparks.end(), spark), sparks.end());
            delete spark;
        }
    }
    if(displayText)
        DisplayText();


    if(falling)
    {
        if(fallTimer->GetTicks() > 3000)
            isDead = true;
    }


//    if(drawCircle)
//    {
//        ToggleMusicCircle();
//        DrawMusicCircle();
//    }

//    DrawPlayer();
}


void Player::StartJump()
{
    if(jump || falling)
        return; // if we're already jumping, don't allow another jump

    jump = true;
    falling = false;
    jumpVelocity = 6.0;
    initialY = yPos;
}

void Player::Jump()
{
    jumpVelocity += gravity * DeltaTime::GetDeltaTime();
    prevYPos = yPos;
    yPos += jumpVelocity * DeltaTime::GetDeltaTime();

    if(jumpVelocity <= 0 && !falling)
    {
        falling = true;
        jump = false;
        fallTimer->Start();
        return;
    }

    CheckTriggerCollision(); // check for text or level triggers
    CheckHealthPackCollision();

    if(CheckCollision())
    {
        jump = false;
//        falling = false;
//        fallTimer->Stop();
        yPos = prevYPos;
        return;
    }
    AudioEngine::SetPosition(xPos, yPos);
    chord->SetPosition(xPos, yPos);
}

void Player::ApplyGravity()
{
    if(DeltaTime::GetDeltaTime() > 0.2f)
        return; // kill if delta time is too high

    if(!falling && fallVelocity < 0)
    {
        falling = true;
        fallTimer->Start();
    }

    fallVelocity += gravity * DeltaTime::GetDeltaTime();

    if(fallVelocity < sqrt(2 * gravity))
        fallVelocity =  sqrt(2 * gravity); // set to terminal velocity

    prevYPos = yPos;
    yPos += fallVelocity * DeltaTime::GetDeltaTime();

    CheckTriggerCollision(); // check for text or level triggers
    CheckHealthPackCollision();

    if(CheckCollision())
    {
        fallVelocity = 0;
        yPos = prevYPos;
        falling = false;
        fallTimer->Stop();
        return;
    }

    AudioEngine::SetPosition(xPos, yPos);
    chord->SetPosition(xPos, yPos);
}

void Player::StartMove(float dir)
{
    if(pushBack) return;

    xDirection = dir;
    moving = true;
}

void Player::MoveLeft()
{
    if(pushBack)
        return;

    slowDown = false;

    xDirection = -1.0;

    if(acceleration > -maxAcceleration)
        acceleration -= accelRate;

    if(acceleration < -maxAcceleration)
        acceleration = -maxAcceleration;

    prevXPos = xPos;
    xPos -= (xDirection * acceleration) * DeltaTime::GetDeltaTime();

    CheckTriggerCollision(); // check for text or level triggers
    CheckHealthPackCollision();

    if(CheckCollision())
    {falling = true;
        fallTimer->Start();
//        GLScene::keyboardAndMouse->SetKey("MoveLeft", false);
        xPos = prevXPos;
//        moving = false;
//        xDirection = 0;
        acceleration = 0;
        return;
    }
    AudioEngine::SetPosition(xPos, yPos);
    chord->SetPosition(xPos, yPos);
}

void Player::MoveRight()
{
    if(pushBack)
        return;

    slowDown = false;

    xDirection = 1.0;

    if(acceleration < maxAcceleration)
        acceleration += accelRate;

    if(acceleration > maxAcceleration)
        acceleration = maxAcceleration;

    prevXPos = xPos;
    xPos += (xDirection * acceleration) * DeltaTime::GetDeltaTime();

    CheckTriggerCollision(); // check for text or level triggers
    CheckHealthPackCollision();

    if(CheckCollision())
    {

//        GLScene::keyboardAndMouse->SetKey("MoveRight", false);
        xPos = prevXPos;
//        moving = false;
//        xDirection = 0;
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

        CheckTriggerCollision(); // check for text or level triggers
        CheckHealthPackCollision();

        if(CheckCollision())
        {
            xPos = prevXPos;
            moving = false;
            slowDown = false;
//            xDirection = 0;
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


        CheckTriggerCollision(); // check for text or level triggers
        CheckHealthPackCollision();

        if(CheckCollision())
        {
                        cout << "STOPPING COLLISION" << endl;

            xPos = prevXPos;
            moving = false;
            slowDown = false;
//            xDirection = 0;
            acceleration = 0;
            return;
        }
        AudioEngine::SetPosition(xPos, yPos);
        chord->SetPosition(xPos, yPos);
    }

}

bool Player::CheckCollision()
{
    for(auto& model : SceneManager::GetActiveScene()->staticObjects)
    {
        if(Collision(model))
            return true;
    }

    return false;
}

void Player::CheckTriggerCollision()
{
    double widthOffset = width / 2, heightOffset = height / 2;

    bool collideLevelTrigger = false;

//    if(nextLevelTrigger)
//    {
//        // Check level trigger collision
//        collideLevelTrigger = (OverlapTrigger(xPos - widthOffset, xPos + widthOffset,
//                                    nextLevelTrigger->GetX() - nextLevelTrigger->GetWidth() / 2,
//                                    nextLevelTrigger->GetX() + nextLevelTrigger->GetWidth() / 2) &&
//                                    OverlapTrigger(yPos - heightOffset, yPos + heightOffset,
//                                    nextLevelTrigger->GetY() - nextLevelTrigger->GetHeight() / 2,
//                                    nextLevelTrigger->GetY() + nextLevelTrigger->GetHeight() / 2));
//    }


    bool insideTrigger = false; // track if we've hit any triggers at all. IF we haven't, we want to disable text display

    for(auto& trigger : textTriggers)
    {
        bool overlapTrigger = (OverlapTrigger(xPos - widthOffset, xPos + widthOffset,
                                trigger->GetX() - trigger->GetWidth() / 2,
                                trigger->GetX() + trigger->GetWidth() / 2) &&
                                OverlapTrigger(yPos - heightOffset, yPos + heightOffset,
                                trigger->GetY() - trigger->GetHeight() / 2,
                                trigger->GetY() + trigger->GetHeight() / 2));

        if(overlapTrigger)
        {
            // DISPLAY TEXT
            textToDisplay = trigger->GetText();
            displayText = true;
            insideTrigger = true;
        }
    }

    // Basically this will check if we've left the trigger area and it will stop displaying text.
    if(!insideTrigger)
        displayText = false;
}

void Player::CheckEnemyCollision()
{
    if(invincible)
        return; // if player is invincible, then we don't check for enemy collision

    for(auto& enemy : SceneManager::GetActiveScene()->enemies)
    {
        if(Collision(enemy))
        {
            TakeDamage(1);

            if(enemy->GetX() > xPos)
                // if we're on left side of enemy and touch them, push back to the left
                StartPushBack(-1.0);
            else if(enemy->GetX() < xPos)
                // if we're on right side of enemy and touch them, push back right.
                StartPushBack(1.0);
            else
                StartPushBack(prevXDirection);
        }
    }
}

void Player::StartPushBack(double direction)
{
    pushBack = true;
    pushDir = direction;
//    xDirection = direction;

    if(direction < 0)
        acceleration = -pushAccel;
    else if(direction > 0)
        acceleration = pushAccel;
    else
        acceleration = pushAccel * prevXDirection;
}


void Player::PushBack()
{

// if we're pushing right, execute different code

    if(pushDir > 0)
    {
        if(acceleration > 0)
            acceleration -= pushDecel;
        else
        {
            pushBack = false; // once acceleration is 0, we no longer need to slow down.
            acceleration = 0; // acceleration is back to baseline
        }

        prevXPos = xPos;
        xPos += (acceleration) * DeltaTime::GetDeltaTime();

        CheckTriggerCollision(); // check for text or level triggers
        CheckHealthPackCollision();

        if(CheckCollision())
        {
            xPos = prevXPos;
            moving = false;
            slowDown = false;
            pushBack = false;
            xDirection = 0;
            acceleration = 0;
            return;
        }
        AudioEngine::SetPosition(xPos, yPos);
        chord->SetPosition(xPos, yPos);
    }
    if(pushDir < 0)
    {
        if(acceleration < 0)
            acceleration += pushDecel;
        else
        {
            pushBack = false; // once acceleration is 0, we no longer need to slow down.
            acceleration = 0; // acceleration is back to baseline
        }

        prevXPos = xPos;
        xPos += (acceleration) * DeltaTime::GetDeltaTime();

        CheckTriggerCollision(); // check for text or level triggers
        CheckHealthPackCollision();

        if(CheckCollision())
        {
            xPos = prevXPos;
            moving = false;
            slowDown = false;
            pushBack = false;
            xDirection = 0;
            acceleration = 0;
            return;
        }
        AudioEngine::SetPosition(xPos, yPos);
        chord->SetPosition(xPos, yPos);
    }
}

void Player::CheckHealthPackCollision()
{
    for(auto& healthPack : SceneManager::GetActiveScene()->healthPacks)
    {
        if(Collision(healthPack))
            ConsumeHealthPack(healthPack);
    }
}

void Player::ConsumeHealthPack(Model* healthPack)
{
    hp += 2; // add 2 to player hp

    if(hp > 10)
        hp = 10; // clamp HP to a maximum of 10

//    auto findHealthPack = find(SceneManager::GetActiveScene()->healthPacks.begin(), SceneManager::GetActiveScene()->healthPacks.end(), healthPack);
//    SceneManager::GetActiveScene()->healthPacks.erase(findHealthPack);
    SceneManager::GetActiveScene()->healthPacks.erase(std::remove(SceneManager::GetActiveScene()->healthPacks.begin(), SceneManager::GetActiveScene()->healthPacks.end(), healthPack), SceneManager::GetActiveScene()->healthPacks.end());
}


bool Player::CheckCircleCollision()
{
    return false;
}

bool Player::CheckCircleSquareCollision()
{
    return false;
}

bool Player::OverlapTrigger(double min0, double max0, double min1, double max1)
{
    return max0 >= min1 && min0 <= max1;
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
    attacking = true;
    Projectile *newProjectile = new Projectile(xPos, yPos, 0.4, 0.5, 1, 4.0, "MusicNote", "PlayerProjectile", x + xPos, y + yPos); // sends relative mouse pointer location
    vector<string> animNames = {"Images/music_note.png"};
    newProjectile->InitAnimations(animNames);

    sparks.push_back(new Particles());
    sparks.back()->GenerateSparks(xPos, yPos, xDirection);
//    newProjectile->InitModel("Images/Note.png", true);
    chord->PlayChord(chordManager->GetNextChord());
    SceneManager::GetActiveScene()->movableObjects.push_back(newProjectile);
}

void Player::UpdateIcons()
{
//    inputIcon->SetPosition(xPos, yPos + height / 1.5);
//    inputIcon->InitModel(iconNames[activeInput], true);

    icons[0]->SetPosition(xPos - width / 1.5, yPos);
    icons[1]->SetPosition(xPos + width / 1.5, yPos);

    if(playingChords)
    {
//        glEnable(GL_TEXTURE_2D);
        icons[activeInput]->DrawModel();
//        glDisable(GL_TEXTURE_2D);
    }
//        inputIcon->DrawModel();

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
        activeInput = rand() % iconNames.size();
//        activeInput = rand() % icons.size();

//        chordTimer->Start();

        chordManager->StartNewSequence();
    }
//    else
//        chordTimer->Stop();

}

// Used within Player class to re-random the next input, reset chordTimer, and grab the next chord.
//Called when player inputs correctly or when timing window has passed while holding shift.
void Player::NextInput()
{
    srand(time(NULL));
    activeInput = rand() % iconNames.size();

    chordTimer->Reset();
}


void Player::CheckUserInput(int userInput, double mouseX, double mouseY)
{
    if(!canPlay)
        // stop execution if waiting for cooldown
        return;

    if(activeInput == userInput)
    {
        double screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
        double screenWidth = GetSystemMetrics(SM_CXSCREEN); //
        double aspectRatio = screenWidth / screenHeight;
        double mousePosX = (mouseX / (screenWidth / 2) - 1.0) * aspectRatio * 3.33;
        double mousePosY = -(mouseY / (screenHeight / 2) - 1.0) * 3.33;
        ShootProjectile(mousePosX, mousePosY);

        // reset input check
//        NextInput();

        // OLD CODE FOR CIRCLE AOE ATTACK
//        circleTimer->Start(); // start timer
//        musicCircle->SetPosition(xPos, yPos);
//        drawCircle = true; // used in Update()
//        CheckHit();
//    }
//    else
//    {
//        // Cooldown is the timing window minus the difference between the timing window and whatever my ticks were when I failed the input check
//        cooldownTargetTime = (chordTimingWindow + (chordTimingWindow - chordTimer->GetTicks()));
//
//        cout << cooldownTargetTime << endl;
//        // set a cooldown for player
//        cooldownTimer->Start();
//
//        PlayChords(false);
//        canPlay =  false;
//    }
    }
}

void Player::UpdateCooldownTimer()
{
    if(cooldownTimer->GetTicks() > cooldownTargetTime)
    {
        canPlay = true;
        cooldownTimer->Stop();
        cooldownTargetTime = 0;
        PlayChords(true);
    }
}

void Player::ToggleMusicCircle()
{
    // if the circle has been drawn for 0.1 seconds, we want to stop drawing it.
    if(circleTimer->GetTicks() > 100)
    {
        drawCircle = false;
        circleTimer->Stop();
    }
}

void Player::DrawMusicCircle()
{
    musicCircle->SetPosition(xPos, yPos);
    musicCircle->DrawModel();
}

void Player::CheckHit()
{
    for(auto& enemy : SceneManager::GetActiveScene()->movableObjects)
    {
        if(enemy->GetTag() == "Player")
            continue;

        if(musicCircle->CollisionCircle(enemy)) // see if we collide with enemies
            cout << "Chord Hit " << enemy->GetName() << endl;
    }
}

void Player::TakeDamage(int damage)
{
    hp -= damage;

    if(hp <= 0)
    {
        isDead = true;
        return;
    }




    SetInvincible(); // set player to invincible after taking damage
}

int Player::getHP()
{
    return hp;
}

void Player::AddTextTrigger(Trigger* newTrigger)
{
    textTriggers.push_back(newTrigger);
}

void Player::CheckInvincible()
{
    if(invincibleTimer->GetTicks() > invincibleTime * 1000)
    {
        invincible = false;
        invincibleTimer->Stop();
        invincibleFrameTimer->Stop();
    }
}

void Player::SetInvincible()
{
    if(invincible)
        return; // safety check to make sure we aren't already invincible.

    invincible = true;
    invincibleFrame = 1;
    invincibleTimer->Start();
    invincibleFrameTimer->Start();
}

bool Player::IsInvincible()
{
    return invincible;
}

void Player::DisplayText()
{
    glPushMatrix();
	glLoadIdentity();
	 //glUseProgram(shaderFont->program);
	//glTranslatef(50,25,0);
	glColor3f (1.0, 0.84, 0); // white font

	// Note that the print function uses screen pixel coordinates, not openGL coordinates.
	// Since our player is always center screen, we can use screen width and height each divided by 2 and add an offset to get the text where we want.
	freetype::print(test1_font, GetSystemMetrics(SM_CXSCREEN) / 2 - 125, GetSystemMetrics(SM_CYSCREEN) / 2 + 100, textToDisplay.c_str());

//	freetype::print(test1_font, GetSystemMetrics(SM_CXSCREEN) / 2 + 100, GetSystemMetrics(SM_CYSCREEN) / 2 + 100,"Test1: Active Freetype Text");
	glPopMatrix();
}

bool Player::IsDead()
{
    return isDead;
}
