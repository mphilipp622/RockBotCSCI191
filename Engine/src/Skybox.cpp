#include <Skybox.h>

TextureLoader texLoader[6];

Skybox::Skybox()
{
    //ctor
    translateX = 0;
    translateY = 0;
    translateZ = 0;

    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;
}

Skybox::~Skybox()
{
    //dtor
}

void Skybox::LoadTextures()
{
    glEnable(GL_TEXTURE_2D);
//    glGenTextures(6, tex);

    texLoader[0].BindTexture("Images/front.jpg");
    texLoader[1].BindTexture("Images/back.jpg");
    texLoader[2].BindTexture("Images/left.jpg");
    texLoader[3].BindTexture("Images/right.jpg");
    texLoader[4].BindTexture("Images/top.jpg");
    texLoader[5].BindTexture("Images/bottom.jpg");
}

void Skybox::DrawBox()
{
    // front face
//    glBindTexture(GL_TEXTURE_2D, tex[0]);

    texLoader[0].Binder();

    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, 1.0, 1.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, 1.0, 1.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);

    glEnd();

    /// Back Face
    texLoader[1].Binder();

    glBegin(GL_QUADS);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(-1.0, 1.0, -1.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.0, 1.0, -1.0);

    glEnd();

        /// top Face
    texLoader[2].Binder();

    glBegin(GL_QUADS);

    glTexCoord2f(0, 1);
    glVertex3f(1.0, 1.0, -1.0);

    glTexCoord2f(0, 0);
    glVertex3f(1.0, 1.0, 1.0);

    glTexCoord2f(1, 0);
    glVertex3f(-1.0, 1.0, 1.0);

    glTexCoord2f(1, 1);
    glVertex3f(-1.0, 1.0, -1.0);

    glEnd();

        /// bottom Face
    texLoader[3].Binder();

    glBegin(GL_QUADS);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);

    glTexCoord2f(0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);

    glTexCoord2f(0.0, 0);
    glVertex3f(1.0, -1.0, 1.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);

    glEnd();

        /// left Face
    texLoader[4].Binder();

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0.0);
    glVertex3f(-1.0, 1.0, 1.0);

    glTexCoord2f(1.0, 0);
    glVertex3f(-1.0, -1.0, 1.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);

    glEnd();

        /// right Face
    texLoader[5].Binder();

    glBegin(GL_QUADS);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, -1.0, 1.0);

    glTexCoord2f(1.0, 1);
    glVertex3f(1.0, -1.0, -1.0);

    glTexCoord2f(0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);

    glTexCoord2f(0.0, 0);
    glVertex3f(1.0, 1.0, 1.0);

    glEnd();
}
