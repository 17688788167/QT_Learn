#ifndef LIGHTBASE_H
#define LIGHTBASE_H
#include <data.h>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>
#include <QVector3D>

class LightBase
{


public:
        LightBase(QOpenGLFunctions_3_3_Core* glfun,const QVector3D& light);
        void Draw(QOpenGLShaderProgram &shader);

        QVector3D m_lightColor;
    private:
        void setupMesh();
        FGLData m_gldata;

        QOpenGLFunctions_3_3_Core * m_glFuns;
};

#endif // LIGHTBASE_H
