#ifndef ACTOR_H
#define ACTOR_H
#include "scene.h"
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <data.h>

class Actor:public Scene,QOpenGLFunctions_3_3_Core
{
public:
    Actor();
    Actor(float Scale, float xOffset, float yOffset,const QString&VertexCodeFile,const QString&FragmentCodeFile);
    ~Actor();

    FGLData glData;


float *ModelVertices;



void GenModelVerticesData(float Scale, float xOffset, float yOffset);

void DrawActor();

QOpenGLShaderProgram m_shader;

};

#endif // ACTOR_H
