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
    Actor(MyOpenglWidget* openGLWidget,const QString&VertexCodeFile,const QString&FragmentCodeFile);

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
QVector3D Position;
QVector3D Scale;
QVector3D Axis;
float Angle;

QMatrix4x4 model;

void InitModel(const QVector3D& Scale,const QVector3D& Position,float angle,const QVector3D& axis);

void AddActorLocation(const QVector3D& LocOffset);

void Rotate();

void UpdateModel();
};

#endif // ACTOR_H
