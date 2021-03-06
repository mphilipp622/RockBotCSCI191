#include <Parallax.h>
#include <TextureLoader.h>
#include <DeltaTime.h>

TextureLoader *backgroundTexture = new TextureLoader();

Parallax::Parallax()
{
    xMax = 1.0f;
    yMax = 0.0f;
    xMin = 0.0f;
    yMin = 1.0f;
}

Parallax::~Parallax()
{
    //dtor
}

void Parallax::DrawSquare(float width, float height)
{
    glColor4f(1.0,1.0,1.0, 1.0);
    backgroundTexture->Binder();
    glBegin(GL_POLYGON);
        glTexCoord2f(xMin,yMin);
        glVertex3f(-width/height,-1,-10.0f);

        glTexCoord2f(xMax,yMin);
        glVertex3f(width/height,-1,-10.0f);

        glTexCoord2f(xMax,yMax);
        glVertex3f(width/height,1,-10.0f);

        glTexCoord2f(xMin,yMax);
        glVertex3f(-width/height,1,-10.0f);
     glEnd();
}

void Parallax::ParallaxInit(string fileName)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // blends object to background color instead. Change it to mess with cool effects

    textureName = fileName;
    cout << "Loading Parallax: " << fileName << endl;
    backgroundTexture->BindTexture(fileName);
}

// Scrolls the background based on directions
void Parallax::Scroll(bool Auto, string dir, float speed)
{
    if(Auto)
    {
        if(dir == "up")
        {
            yMin -= speed * DeltaTime::GetDeltaTime();
            yMax -= speed * DeltaTime::GetDeltaTime();
        }
        if(dir == "down")
        {

            yMin += speed * DeltaTime::GetDeltaTime();
            yMax += speed * DeltaTime::GetDeltaTime();
        }
        if(dir == "left")
        {
            xMin -= speed * DeltaTime::GetDeltaTime();;
            xMax -= speed * DeltaTime::GetDeltaTime();;
        }
        if(dir == "right")
        {
            xMin += speed * DeltaTime::GetDeltaTime();;
            xMax += speed * DeltaTime::GetDeltaTime();;
        }
    }
}

string Parallax::GetTextureName()
{
    return textureName;
}
