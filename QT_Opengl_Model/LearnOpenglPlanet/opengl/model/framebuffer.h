#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H


#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLFramebufferObject>

class MyOpenglWidget;

class frameBuffer
{
public:
    frameBuffer(QOpenGLFunctions_3_3_Core * glfuns,MyOpenglWidget* glwidget);
    ~frameBuffer();
    void initScreen();
    void initFbo();
    void initSingleFbo();
    void initMultiFbo();


    void paintScreen();
    void paintSingleScreen();
    void paintMultiScreen();


    void paintFbo();

    void paintSingleFbo();
    void paintMultiFbo();





    void freeScreen();
    void freeFbo();

    void resetFbo();

        QOpenGLFunctions_3_3_Core* m_glfuns;
        MyOpenglWidget* m_glwidget;
     QOpenGLShaderProgram screenShaderProgram;
         QOpenGLVertexArrayObject screenVao;
         QOpenGLBuffer screenVbo;
        QOpenGLShaderProgram fboShaderProgram;

     QOpenGLVertexArrayObject fboCubeVao, fboPlaneVao;

    QOpenGLBuffer fboCubeVbo, fboPlaneVbo;
     QOpenGLFramebufferObject *fboBuffer{ nullptr };


     QOpenGLTexture *fboCubeTexture{ nullptr }, *fboPlaneTexture{ nullptr };


    QOpenGLTexture* screenTexture;

    unsigned int VAO,VBO;

    unsigned int framebuffer;
     unsigned int textureColorbuffer;
     unsigned int rbo;


     unsigned int fboMultiSample;
     unsigned int rboMultiSample;
     unsigned int multiSampleTex;


public:

};

#endif // FRAMEBUFFER_H

