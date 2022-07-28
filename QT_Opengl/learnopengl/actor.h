#ifndef ACTOR_H
#define ACTOR_H
#include "scene.h"
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

class Actor:public Scene,QOpenGLFunctions_3_3_Core
{
public:
    Actor();
    ~Actor();
unsigned int ActorVBO,ActorVAO;
float *ModelVertices;
QOpenGLShaderProgram shaderProgram;




void DrawActor();

void GenModelVerticesData(float Scale, float xOffset, float yOffset);


};

#endif // ACTOR_H
