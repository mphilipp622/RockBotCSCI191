#include <Player.h>
#include <Timer.h>
#include <TextureLoader.h>
#include <string>
#include <GLScene.h>

Timer *T = new Timer();
TextureLoader run[10];
TextureLoader idle[1];
TextureLoader jumpAnim[1];

Player::Player()
{
    // Collision
    width = 1.0;
    height = 1.0;

    // set previous positions to our starting position
    prevXPos = xPos;
    prevYPos = yPos;

    // Initialize Quad
    vertices[0].x = 0.0;
    vertices[0].y = 0.0;
    vertices[0].z = -1.0;

    vertices[1].x = width;
    vertices[1].y = 0.0;
    vertices[1].z = -1.0;

    vertices[2].x = width;
    vertices[2].y = height;
    vertices[2].z = -1.0;

    vertices[3].x = 0.0;
    vertices[3].y = height;
    vertices[3].z = -1.0;

    moveSpeed = 1.0;
    jumpSpeed = 1.0;
    hp = 3;
    actionTrigger = 0;

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

    T->Start();

//    InitPlayer();
}

Player::~Player()
{
    //dtor
}

//void Player::SetVertices()
//{
//    height += 0.1;
//    width += 0.1;
//
//    // Initialize Quad
//    vertices[0].x = 0.0;
//    vertices[0].y = 0.0;
//    vertices[0].z = -1.0;
//
//    vertices[1].x = width;
//    vertices[1].y = 0.0;
//    vertices[1].z = -1.0;
//
//    vertices[2].x = width;
//    vertices[2].y = height;
//    vertices[2].z = -1.0;
//
//    vertices[3].x = 0.0;
//    vertices[3].y = height;
//    vertices[3].z = -1.0;
//}
void Player::DrawPlayer()
{
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

//    glPushMatrix();

    glTexCoord2f(0.0, 1.0);
    glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

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
    run[0].BindTexture("Images/Player/player0.png");
    run[1].BindTexture("Images/Player/player1.png");
    run[2].BindTexture("Images/Player/player2.png");
    run[3].BindTexture("Images/Player/player3.png");
    run[4].BindTexture("Images/Player/player4.png");
    run[5].BindTexture("Images/Player/player5.png");
    run[6].BindTexture("Images/Player/player6.png");
    run[7].BindTexture("Images/Player/player7.png");
    run[8].BindTexture("Images/Player/player8.png");
    run[9].BindTexture("Images/Player/player9.png");

    idle[0].BindTexture("Images/Player/play.png");

    jumpAnim[0].BindTexture("Images/Player/player0.png");
}

void Player::Actions(int newAction)
{
    switch(newAction)
    {
    case 0:
        glPushMatrix();

        glTranslated(xPos, yPos, -1.0);
        idle[0].Binder();
        DrawPlayer();

        glPopMatrix();
        break;

    case 1:
        glPushMatrix();

        glTranslated(xPos, yPos, -1.0);
        if(T->GetTicks() > 15)
        {
            moveSpeed++;
            moveSpeed %= 10;
            T->Reset();
        }

        run[moveSpeed].Binder();
        DrawPlayer();

        glPopMatrix();
        break;
    case 2:
        glPushMatrix();

        glTranslated(xPos, yPos, -1.0);
        jumpAnim[0].Binder();
        DrawPlayer();

        glPopMatrix();
        break;
    }
}

void Player::Update()
{
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
        Actions(2);
    }
    else
        ApplyGravity();

    if(slowDown)
        StopMove();

    CheckCollision();

//   cout <<"" << endl; // WHY? Why does it need something here?
}

void Player::NormalAttack(bool newVal)
{
    if(newVal)
    {
        cout << "attacking" << endl;
    }

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
//    if(yPos < jumpY)
    jumpVelocity += gravity * DeltaTime::GetDeltaTime();
    prevYPos = yPos;
    yPos += jumpVelocity * DeltaTime::GetDeltaTime();
    if(yPos <= initialY)
    {
        yPos = initialY;
        jump = false;
    }
}

void Player::ApplyGravity()
{
    prevYPos = yPos;
    yPos += gravity * DeltaTime::GetDeltaTime() * 0.01;
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

void Player::CheckCollision()
{
    for(auto& model : GLScene::staticObjects)
    {
        if(Collision(model) && !GroundCheck(model))
        {
            xPos = prevXPos;
            yPos = prevYPos;
            cout << "Collide With " << model->GetName() << endl;
//            if(GroundCheck(model))
//                cout << "Hi" << endl;
//                jump = false;
        }
        else if(Collision(model) && GroundCheck(model))
        {
            cout << "Ground Check " << model->GetName() << endl;
            yPos = prevYPos;
        }
//            jump = false;
//            cout << "Collision with " << model->GetName() << endl;
//        else cout << " " << endl;
    }
}
