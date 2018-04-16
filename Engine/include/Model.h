#ifndef MODEL_H
#define MODEL_H

#include <windows.h>
<<<<<<< HEAD
#include "glut.h"
#include <string>
=======
#include <glut.h>
#include <string>
#include <TextureLoader.h>
<<<<<<< HEAD
>>>>>>> master
=======
#include <AudioSource.h>
#include <cmath>
>>>>>>> master

using namespace std;

typedef struct
{
    float x, y, z;
}vec;

class Model
{
    public:
        Model();
        Model(float, float, double, double, string, string);
        Model(float, float, double, double, string, string, AudioSource*);
        virtual ~Model();
        void DrawModel();
<<<<<<< HEAD
        void InitModel(char* fileName, bool transparent);
=======
        void InitModel(string fileName, bool transparent);
>>>>>>> master

        void InitPlayer();

        double rotateX, rotateY, rotateZ;
        double zoom;
//        string direction;
        vec vertices[4];

        // collision getters
        double GetX();
        double GetY();
        double GetRadius();
        float GetWidth();
        float GetHeight();
        void SetPosition(double, double);
        void SetWidth(double);

<<<<<<< HEAD
=======
        virtual void Update();

<<<<<<< HEAD
>>>>>>> master
=======
        AudioSource* GetAudioSource();

        bool Collision(Model*);
        bool CollisionCircle(Model*);
        bool CollisionCircleSquare(Model*);

>>>>>>> master
        string GetName();
        string GetTag();

    protected:
        float width, height, radius;
        double xPos, yPos;
<<<<<<< HEAD
        string name;
        bool GroundCheck(Model*);
        bool Collision(Model*);
<<<<<<< HEAD
=======
=======
        string name, tag;
>>>>>>> master
        TextureLoader *texture;

        // This model will check square-to-square collision with other objects. Useful for certain types of environmental collision maybe
        virtual bool CheckCollision();
>>>>>>> master

        // This model will check circle-to-circle collision with other objects. Useful for checking player-to-enemy or player-to-projectile collision.
        virtual bool CheckCircleCollision();

        // This model will check circle-to-square collision. Useful for player and enemy models checking collision with platforms
        virtual bool CheckCircleSquareCollision();

        AudioSource* audioSource;

    private:
        bool Overlapping(double min0, double max0, double min1, double max1);
        bool OverlappingCircles(double x0, double y0, double x1, double y1, double r0, double r1);
};

#endif // MODEL_H
