#ifndef LIGHTBASE_H
#define LIGHTBASE_H
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QMatrix4x4>
#include <data.h>
#include "myopenglwidget.h"
class LightBase
{
public:
    LightBase();
    LightBase(MyOpenglWidget* OpenglWidget);

    unsigned int VAO;
    unsigned int VBO;

    QOpenGLShaderProgram m_shader;
protected:
    MyOpenglWidget* m_OpenglWidget;
};

#endif // LIGHTBASE_H
