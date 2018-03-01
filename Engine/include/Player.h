#ifndef PLAYER_H
#define PLAYER_H

#include "GL/gl.h"
#include <Model.h>
#include <TextureLoader.h>

typedef struct
{
    float x, y, z;
}vec1;

// class for player character. Inherits from Model for positions/rotations/etc.
class Player
{
    public:
        Player();
        virtual ~Player();

        float scaleSize[3] = {1.0, 1.0, 1.0}; // x, y, z scale values
        vec1 vertices[4]; // 4 vertices of xyz values

        // player stats
        int hp;
        float moveSpeed, jumpSpeed;

        void DrawPlayer();
        void InitPlayer();
        void Actions();

    protected:

    private:
};

#endif // PLAYER_H
