#include "Projectile.h"
#include <cmath>

Projectile::Projectile()
{
    //ctor
}

Projectile::~Projectile()
{
    //dtor
}
Projectile::Projectile(double newX, double newY, double newWidth, double newHeight, int newDamage, float newSpeed, string newName, string newTag, double newTargetX, double newTargetY)
{
    xPos = newX;
    yPos = newY;

    prevX = newX;
    prevY = newY;

    targetX = newTargetX;
    targetY = newTargetY;

    damage = newDamage;
    speed = newSpeed;

    name = newName;
    tag = newTag;

    vectorDist = sqrt(pow((targetX - xPos), 2) + pow((targetY - yPos), 2));
    normalizedX = (targetX - xPos) / vectorDist;
    normalizedY = (targetY - yPos) / vectorDist;

    width = newWidth;
    height = newHeight;

    endOfLifeTime = 5000; // 5 seconds

    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    // translations
    zoom = 0;

    // Initialize Quad
    vertices[0].x = -width / 2;
    vertices[0].y = -height / 2;
    vertices[0].z = zoom;

    vertices[1].x = width / 2;
    vertices[1].y = -height / 2;
    vertices[1].z = zoom;

    vertices[2].x = width / 2;
    vertices[2].y = height / 2;
    vertices[2].z = zoom;

    vertices[3].x = -width / 2;
    vertices[3].y = height / 2;
    vertices[3].z = zoom;

    texture = new TextureLoader();
    lifetime = new Timer();
    frameTimer = new Timer();

//    shader = new LoadShader();
//    shader->ShaderInit("Shaders/v1.vs", "Shaders/f1.fs");

//    testShader->BindTexture("Images/MilkyWay.jpg");



    // PARTICLE CREATION
    particle = new Particles();
    particle->GenerateMusicParticles(xPos, yPos, width, height);
    lifetime->Start();
    frameTimer->Start();
}

void Projectile::Update()
{
    Move();

//    DisplayParticles();
    if(tag == "EnemyProjectile")
        Animate();
    else
        DrawModel();


    if(lifetime->GetTicks() > endOfLifeTime)
        Destroy();
}

void Projectile::Move()
{
    prevX = xPos;
    prevY = yPos;

    xPos += normalizedX * speed * DeltaTime::GetDeltaTime();
    yPos += normalizedY * speed * DeltaTime::GetDeltaTime();

    xDir = xPos - prevX;
    yDir = yPos - prevY;

    if(CheckCollision())
        // if we collide with something, destroy object. If object is enemy, we need to deal damage
        Destroy();
    if(tag == "PlayerProjectile" && CheckCollisionEnemy())
        Destroy(); // implement damage code here later
    if(tag == "EnemyProjectile" && Collision(Player::player))
    {
        Player::player->TakeDamage(damage); // deal damage to player
        Destroy(); // destroy projectile
    }

}

///////////////////////////////////
// RENDER PARTICLES
///////////////////////////////////
void Projectile::DisplayParticles()
{
    // This is called in DrawGLScene. Make sure it is uncommented in DrawGLScene

    glPushMatrix();
//    glUseProgram(shader->program);
    glTranslated(xPos, yPos, 0); // sets particle to player x and y position.

    particle->DrawParticles();
    particle->LifetimeMusic(xPos, yPos, xDir, yDir);
//    glUseProgram(0);
    glPopMatrix();
}


void Projectile::InitAnimations(vector<string> names)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for(int i = 0; i < names.size(); i++)
        animation[i].BindTexture(names.at(i));
}

void Projectile::DrawProjectile()
{
     glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

		// flip texture to the right

		glTexCoord2f(0.0, 1.0);
		glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

    glEnd();
}


void Projectile::Animate()
{
    glPushMatrix();

    glTranslated(xPos, yPos, zoom);
    if(frameTimer->GetTicks() > 60)
    {
        frame++;
        frame %= 4;
        frameTimer->Reset();
    }

    animation[frame].Binder();
    DrawProjectile();

    glPopMatrix();
}



bool Projectile::CheckCollision()
{
    for(auto& model : GLScene::staticObjects)
    {
        if(Collision(model))
            return true;
    }


    return false;
}
bool Projectile::CheckCollisionEnemy()
{
    // check for collision with an enemy
    for(auto& enemy : GLScene::enemies)
    {
        if(Collision(enemy))
        {
            enemy->TakeDamage(damage);
            return true; // will ignore player collision.
        }

    }

    return false;
}

bool Projectile::CheckCircleCollision()
{
    return false;
}

bool Projectile::CheckCircleSquareCollision()
{
    return false;
}


void Projectile::Destroy()
{
    // find this projectile in the main vector and remove it. Then delete this projectile
    auto finder = find(GLScene::movableObjects.begin(), GLScene::movableObjects.end(), this);
    GLScene::movableObjects.erase(finder);
    delete this;
}
