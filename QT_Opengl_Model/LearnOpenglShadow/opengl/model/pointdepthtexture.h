#ifndef POINTDEPTHTEXTURE_H
#define POINTDEPTHTEXTURE_H

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLTexture>

class MyOpenglWidget;


class PointDepthTexture
{
public:
    PointDepthTexture();
    PointDepthTexture(QOpenGLFunctions_3_3_Core * glfuns,MyOpenglWidget* glwidget);


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

    void paintFbo();
    void paintScreen();

    unsigned int depthMapFBO;
    unsigned int depthCubemap;
    const unsigned int SHADOW_WIDTH = 1024*2, SHADOW_HEIGHT = 1024*2;
    QVector3D lightPos;
};

#endif // POINTDEPTHTEXTURE_H
