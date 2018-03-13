#include "Projectile.h"

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

    this->targetX = newTargetX;
    this->targetY = newTargetY;

    this->damage = newDamage;
    this->speed = newSpeed;

    this->name = newName;

    this->width = newWidth;
    this->height = newHeight;

    this->rotateX = 0;
    this->rotateY = 0;
    this->rotateZ = 0;

    // translations
    this->zoom = -3.0;

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
}

void Projectile::Update()
{
    Move();
}

void Projectile::Move()
{

}
