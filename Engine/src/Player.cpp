#include "Player.h"

TextureLoader* tex = new TextureLoader();

Player::Player()
{
    // Initialize Quad
    vertices[0].x = 0.0;
    vertices[0].y = 0.0;
    vertices[0].z = -1.0;

    vertices[1].x = 1.0;
    vertices[1].y = 0.0;
    vertices[1].z = -1.0;

    vertices[2].x = 1.0;
    vertices[2].y = 1.0;
    vertices[2].z = -1.0;

    vertices[3].x = 0.0;
    vertices[3].y = 1.0;
    vertices[3].z = -1.0;

    moveSpeed = 1.0;
    jumpSpeed = 1.0;
    hp = 3;

    InitPlayer();
}

Player::~Player()
{
    //dtor
}

void Player::DrawPlayer()
{
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();

    glTexCoord2f(0.0, 1.0);
    glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

    glPopMatrix();

}

void Player::InitPlayer()
{
    // player must always render last in the scene
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Player::Actions()
{

}
