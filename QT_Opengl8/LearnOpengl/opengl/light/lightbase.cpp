#include "lightbase.h"

LightBase::LightBase()
{




}

LightBase::LightBase(MyOpenglWidget *OpenglWidget)
{
    this->m_OpenglWidget=OpenglWidget;

    bool success;
    success= m_shader.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shader/light.vert");
    if(!success)
         qDebug()<<"打开顶点着色器失败:"<<m_shader.log();
    success= m_shader.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shader/light.frag");
    if(!success)
         qDebug()<<"打开片段着色器失败:"<<m_shader.log();

     m_shader.link();
}
