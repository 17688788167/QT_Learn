#ifndef ACTOR_H
#define ACTOR_H
#include "scene.h"
#include <QOpenGLFunctions_3_3_Core>
#include <data.h>

class Actor:public Scene,QOpenGLFunctions_3_3_Core
{
public:
    Actor();
    Actor(float Scale, float xOffset, float yOffset);
    ~Actor();

    FGLData glData;


float *ModelVertices;



void GenModelVerticesData(float Scale, float xOffset, float yOffset);

void DrawActor();

};

#endif // ACTOR_H
