#include "Fonts.h"
#include <Player.h>

Fonts::Fonts()
{
    //ctor
    texture = new TextureLoader();
    zoom = 0;
    xPos = 0;
    yPos = 0;
    charCount = 0;
}

Fonts::~Fonts()
{
    //dtor
}

void Fonts::InitFonts(char* filename)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    texture->Binder();
    texture->BindTexture(filename);
}

void Fonts::BuildFont(char* newLine)
{
    for(int i = 0; i < strlen(newLine); i++)
    {
        if(newLine[i] == 'a')
        {
            C[charCount].xMin = 0;
            C[charCount].xMax = 1.0/17.0;
            C[charCount].yMin = 4.0;
            C[charCount].yMax = 5.0 / 6.0;
        }
        else if(newLine[i] == 'A')
        {
            C[charCount].xMin = 0;
            C[charCount].xMax = 0/17.0;
            C[charCount].yMin = 2.0;
            C[charCount].yMax = 3.0 / 6.0;
        }
        else if(newLine[i] == '!')
        {
            C[charCount].xMin = 0;
            C[charCount].xMax = 1.0 / 17.0;
            C[charCount].yMin = 0;
            C[charCount].yMax = 1.0 / 6.0;
        }

    }
}

void Fonts::DrawFont(int i)
{
    xPos = Player::player->GetX();
    yPos = Player::player->GetY() + 0.5;
    texture->Binder();

    glPushMatrix();
    glTranslated(xPos, yPos, zoom);
    glBegin(GL_QUADS);

    glTexCoord2f(C[i].xMin, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glTexCoord2f(C[i].xMax, 1.0);
    glVertex3f(1.0/17.0, 0.0, 0.0);
    glTexCoord2f(C[i].xMax, 1.0);
    glVertex3f(1.0/17.0, 1.0, 0.0);
    glTexCoord2f(C[i].xMin, 1.0);
    glVertex3f(0, 1.0, 0.0);

    glEnd();
    glPopMatrix();
}
