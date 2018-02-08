#include "Model.h"


Model::Model()
{
    // rotations
    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    // translations
    zoom = -8.0;
    xPos = 0;
    yPos = 0;
}

Model::~Model()
{

}
void Model::DrawModel()
{
    // render this model

    glColor3f(0.5, 0.4, 0.1);
    glTranslated(xPos, yPos, zoom);
    glRotated(rotateX, 1, 0, 0);
    glRotated(rotateY, 0, 1, 0);
    glRotated(rotateZ, 0, 0, 1);

    glutSolidTeapot(1.5);
}
