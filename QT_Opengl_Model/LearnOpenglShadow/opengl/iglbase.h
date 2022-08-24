#ifndef IGLBASE_H
#define IGLBASE_H
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLTexture>
#include "data.h"
#include <QVector3D>

class IGLBase
{
public:

    FGLData m_gldata;
    QOpenGLFunctions_3_3_Core * m_glFuns;
    QOpenGLShaderProgram * m_glShader;
    QOpenGLTexture* m_diffuse;
    QOpenGLTexture* m_specular;

    QVector3D postion;
    QVector3D rotateAxis;
    QVector3D angle;
    QVector3D scale;

    IGLBase(QOpenGLFunctions_3_3_Core* glfun)
    {
        this->m_glFuns=glfun;
    }
    IGLBase(QOpenGLFunctions_3_3_Core* glfun,QOpenGLShaderProgram*glShader)
    {
        this->m_glFuns=glfun;
        this->m_glShader=glShader;
    }
    virtual void setupMesh()=0;
    virtual void Draw(QOpenGLShaderProgram &shader)=0;
    virtual void Draw()=0;
};

#endif // IGLBASE_H
