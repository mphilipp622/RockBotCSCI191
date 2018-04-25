#include "HUD.h"
#include "Player.h"

//Player *playerStats;

HUD::HUD()
{
    //ctor
}

HUD::~HUD()
{
    //dtor
}

void HUD::showHP(Player *playerStats)
{
    //Load in bar images in increments of 10 or such.
    //Display bar based on HP
    //
    double tempX = Player::player->GetX();
    double tempY = Player::player->GetY();
    playerStats->getHP();

    double BarSize = 3.0*(playerStats->getHP()/10.0);
    cout << playerStats->getHP() << " " << BarSize << endl;
    glColor3f(1,0,0);
    glPushMatrix();

    glTranslatef(-4.5+tempX,2+tempY,0);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(BarSize,0,0);
    glVertex3f(BarSize,0.5,0);
    glVertex3f(0,0.5,0);
    //width*(currHP/maxHP);
    glEnd();
    glPopMatrix();



    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(-4.5+tempX,2+tempY,-0.1);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(3,0,0);
    glVertex3f(3,0.5,0);
    glVertex3f(0,0.5,0);
    //width*(currHP/maxHP);
    glEnd();
    glPopMatrix();
}

void HUD::showHeadIcon()
{
    //Display head icon, changes depending on effects.
    //Like taking damage, etc.
}
