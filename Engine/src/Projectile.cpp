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
Projectile::Projectile(double newX, double newY, double newWidth, double newHeight, int newDamage, float newSpeed, string newName, double newTargetX, double newTargetY)
{
    this->xPos = newX;
    this->yPos = newY;

    this->prevX = newX;
    this->prevY = newY;

    this->targetX = newTargetX;
    this->targetY = newTargetY;

    this->damage = newDamage;
    this->speed = newSpeed;

    this->name = newName;

    this->vectorDist = sqrt(pow((this->targetX - this->xPos), 2) + pow((this->targetY - this->yPos), 2));
    this->normalizedX = (this->targetX - this->xPos) / this->vectorDist;
    this->normalizedY = (this->targetY - this->yPos) / this->vectorDist;

    this->width = newWidth;
    this->height = newHeight;

    this->endOfLifeTime = 5000; // 5 seconds

    this->rotateX = 0;
    this->rotateY = 0;
    this->rotateZ = 0;

    // translations
    this->zoom = 0;

    // Initialize Quad
    this->vertices[0].x = -this->width / 2;
    this->vertices[0].y = -this->height / 2;
    this->vertices[0].z = this->zoom;

    this->vertices[1].x = this->width / 2;
    this->vertices[1].y = -this->height / 2;
    this->vertices[1].z = this->zoom;

    this->vertices[2].x = this->width / 2;
    this->vertices[2].y = this->height / 2;
    this->vertices[2].z = this->zoom;

    this->vertices[3].x = -this->width / 2;
    this->vertices[3].y = this->height / 2;
    this->vertices[3].z = this->zoom;

    this->texture = new TextureLoader();
    this->lifetime = new Timer();
    this->lifetime->Start();
}

void Projectile::Update()
{
    this->Move();

    this->DrawModel();

    if(this->lifetime->GetTicks() > this->endOfLifeTime)
        this->Destroy();
}

void Projectile::Move()
{
    this->prevX = this->xPos;
    this->prevY = this->yPos;

    this->xPos += this->normalizedX * this->speed * DeltaTime::GetDeltaTime();
    this->yPos += this->normalizedY * this->speed * DeltaTime::GetDeltaTime();

    if(this->CheckCollision())
        // if we collide with something, destroy object. If object is enemy, we need to deal damage
        this->Destroy();
    if(this->CheckCollisionEnemy())
        return; // implement damage code here later
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
    for(auto& model : GLScene::movableObjects)
    {
        if(Collision(model) && model->GetName() != "player")
            return true; // will ignore player collision.
    }

    return false;
}

void Projectile::Destroy()
{
    // find this projectile in the main vector and remove it. Then delete this projectile
    auto finder = find(GLScene::movableObjects.begin(), GLScene::movableObjects.end(), this);
    GLScene::movableObjects.erase(finder);
    delete this;
}
