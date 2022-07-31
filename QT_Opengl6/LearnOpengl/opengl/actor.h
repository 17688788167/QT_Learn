#ifndef ACTOR_H
#define ACTOR_H
#include "scene.h"
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <data.h>

class MyOpenglWidget;
class Actor:public QOpenGLFunctions_3_3_Core
{
public:
    Actor();
    Actor(MyOpenglWidget* openGLWidget,const QString&VertexCodeFile,const QString&FragmentCodeFile,const QString&TextureFile);

    ~Actor();

    FGLData glData;


float *ModelVertices;

int ModelVerticesSizeof;


void GenModelVerticesData(float Scale, float xOffset, float yOffset,float zOffset);

void DrawActor();

void BindTexture();

//opengl属性
public:
QOpenGLShaderProgram m_shader;
QOpenGLTexture * m_texture;
QOpenGLTexture * m_texture1;
QOpenGLTexture * m_texture2;

MyOpenglWidget * m_openGLWidget;

Scene * scene;

QMatrix4x4 model;

void UpdateModel(float Scale, float xOffset, float yOffset,float zOffset,float angle,const QVector3D& axis);
};

#endif // ACTOR_H
