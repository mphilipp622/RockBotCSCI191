#include "HUD.h"
#include "Player.h"

//Player *playerStats;


HUD::HUD()
{
    //ctor
    //headIcon = new TextureLoader();
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    iconImage[1].BindTexture("Images/head_icon2.png");
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
  //  cout << playerStats->getHP() << " " << BarSize << endl;



    glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(-4.5+tempX,2+tempY,0.1);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(BarSize,0,0);
    glVertex3f(BarSize,0.5,0);
    glVertex3f(0,0.5,0);
    //width*(currHP/maxHP);
    glEnd();
    glPopMatrix();



    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-4.5+tempX,2+tempY,0.05);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(3,0,0);
    glVertex3f(3,0.5,0);
    glVertex3f(0,0.5,0);
    glEnd();
    glPopMatrix();

    //Head Icon

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor4f(1.0,1.0,1.0, 1.0);
    glTranslatef(-4.5+tempX,1+tempY,0.1);
    iconImage[1].Binder();

    glBegin(GL_QUADS);

    glTexCoord2f(0,0);
    glVertex3f(0,0,0);

    glTexCoord2f(1,0);
    glVertex3f(1,0,0);

    glTexCoord2f(1,1);
    glVertex3f(1,1,0);

    glTexCoord2f(0,1);
    glVertex3f(0,1,0);

    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//
//    glPushMatrix();
//    glColor3f(0,0,0);
//    glTranslatef(-4.49+tempX,0.99+tempY,-0.11);
//    glBegin(GL_QUADS);
//    glVertex3f(0,0,0);
//    glVertex3f(1,0,0);
//    glVertex3f(1,1,0);
//    glVertex3f(0,1,0);
//    glEnd();
//    glPopMatrix();
}

void HUD::showHeadIcon()
{

    //Display head icon, changes depending on effects.
    //Like taking damage, etc.
}
