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
        Model(float, float, double, double, string);
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
        float GetWidth();
        float GetHeight();
        void SetPosition(double, double);
        void SetWidth(double);

<<<<<<< HEAD
=======
        virtual void Update();

>>>>>>> master
        string GetName();
    protected:
        float width, height;
        double xPos, yPos;
        string name;
        bool GroundCheck(Model*);
        bool Collision(Model*);
<<<<<<< HEAD
=======
        TextureLoader *texture;
        virtual bool CheckCollision();
>>>>>>> master

    private:
        bool Overlapping(double min0, double max0, double min1, double max1);
        bool OverlapGround(double maxY, double minY);
};

#endif // MODEL_H
