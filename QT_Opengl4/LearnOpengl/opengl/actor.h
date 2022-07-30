#ifndef ACTOR_H
#define ACTOR_H
#include "scene.h"
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <data.h>

class Actor:public Scene,QOpenGLFunctions_3_3_Core
{
public:
    Actor();
    Actor(float Scale, float xOffset, float yOffset,const QString&VertexCodeFile,const QString&FragmentCodeFile,const QString&TextureFile);
    ~Actor();

    FGLData glData;


float ModelVertices[180];
int ModelVerticesSizeof;


void GenModelVerticesData(float Scale, float xOffset, float yOffset);

void DrawActor();

void BindTexture();

//opengl属性
public:
QOpenGLShaderProgram m_shader;
QOpenGLTexture * m_texture;
QOpenGLTexture * m_texture1;
QOpenGLTexture * m_texture2;
};

#endif // ACTOR_H
