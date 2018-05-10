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

    red = 1.0;
    green = 1.0;
    blue = 1.0;

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

    frame = 0;

//    shader = new LoadShader();
//    shader->ShaderInit("Shaders/v1.vs", "Shaders/f1.fs");

//    testShader->BindTexture("Images/MilkyWay.jpg");


    // PARTICLE CREATION
    if(tag != "EnemyProjectile")
    {
        particle = new Particles();
        particle->GenerateMusicParticles(xPos, yPos, width, height);
    }
    else
        particle = nullptr;

    lifetime->Start();
    frameTimer->Start();
}

void Projectile::Update()
{
    Move();

    Animate();

    if(particle)
        DisplayParticles();



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
    if(tag == "EnemyProjectile" && Collision(Player::player) && !Player::player->IsInvincible())
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

//    particle->GenerateMusicParticles(xPos, yPos, width, height);
    particle->LifetimeMusic(xPos, yPos, xDir, yDir, height);
    particle->DrawParticles();

//    glUseProgram(shader->program);
//    glTranslated(xPos, yPos, 0); // sets particle to player x and y position.

//    glUseProgram(0);
}


void Projectile::InitAnimations(vector<string> names)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    frame = 0;

    for(int i = 0; i < names.size(); i++)
    {
        animation.push_back(new TextureLoader());
        animation.back()->BindTexture(names.at(i));
    }
}

void Projectile::DrawProjectile()
{

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
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glColor4f(1.0, 1.0, 1.0, 1.0);
    glTranslated(xPos, yPos, 0);
    if(frameTimer->GetTicks() > 60)
    {
        frame++;
        frame %= animation.size();
        frameTimer->Reset();
    }

    animation[frame]->Binder();
    DrawProjectile();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}



bool Projectile::CheckCollision()
{
    for(auto& model : SceneManager::GetActiveScene()->staticObjects)
    {
        if(Collision(model))
            return true;
    }


    return false;
}
bool Projectile::CheckCollisionEnemy()
{
    // check for collision with an enemy
    for(auto& enemy : SceneManager::GetActiveScene()->enemies)
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
//    auto finder = find(SceneManager::GetActiveScene()->movableObjects.begin(), SceneManager::GetActiveScene()->movableObjects.end(), this);
//    SceneManager::GetActiveScene()->movableObjects.erase(finder);
    SceneManager::GetActiveScene()->movableObjects.erase(std::remove(SceneManager::GetActiveScene()->movableObjects.begin(), SceneManager::GetActiveScene()->movableObjects.end(), this), SceneManager::GetActiveScene()->movableObjects.end());
//    delete particle;
//    delete this;
}
