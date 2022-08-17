#ifndef IGLBASE_H
#define IGLBASE_H
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>
#include "data.h"

class IGLBase
{
public:

    FGLData m_gldata;
    QOpenGLFunctions_3_3_Core * m_glFuns;
    IGLBase(QOpenGLFunctions_3_3_Core* glfun)
    {
        this->m_glFuns=glfun;
        //setupMesh();
    }
    virtual void setupMesh()=0;
    virtual void Draw(QOpenGLShaderProgram &shader)=0;
};

#endif // IGLBASE_H
