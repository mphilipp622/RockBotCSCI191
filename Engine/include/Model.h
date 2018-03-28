#ifndef MODEL_H
#define MODEL_H

#include <windows.h>
#include <glut.h>
#include <string>
#include <TextureLoader.h>
#include <AudioSource.h>

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
        Model(float, float, double, double, string, AudioSource*);
        virtual ~Model();
        void DrawModel();
        void InitModel(string fileName, bool transparent);

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

        virtual void Update();

        AudioSource* GetAudioSource();

        string GetName();
    protected:
        float width, height;
        double xPos, yPos;
        string name;
        bool GroundCheck(Model*);
        bool Collision(Model*);
        TextureLoader *texture;
        virtual bool CheckCollision();
        AudioSource* audioSource;

    private:
        bool Overlapping(double min0, double max0, double min1, double max1);
        bool OverlapGround(double maxY, double minY);
};

#endif // MODEL_H
