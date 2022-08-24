#ifndef MYDEPTHTEXTURE_H
#define MYDEPTHTEXTURE_H

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLTexture>

class MyOpenglWidget;

class MyDepthTexture
{
public:

    MyDepthTexture(QOpenGLFunctions_3_3_Core * glfuns,MyOpenglWidget* glwidget);
    MyDepthTexture();

    QOpenGLFunctions_3_3_Core* m_glfuns;
    MyOpenglWidget* m_glwidget;
    QOpenGLShaderProgram screenShaderProgram;
    QOpenGLShaderProgram m_DepthMapShaderProgram;


    QOpenGLShaderProgram fboShaderProgram;
    QOpenGLTexture* screenTexture;

    unsigned int VAO,VBO;

     unsigned int framebuffer;
     unsigned int textureColorbuffer;
     unsigned int rbo;


    void initScreen();
    void initFbo();

    void paintFbo(const QMatrix4x4& lightSpaceMatrix);
    void paintScreen();

    unsigned int depthMapFBO;
};

#endif // MYDEPTHTEXTURE_H
