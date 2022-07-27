#include "xxopenglwidget.h"

XXOpenGlWidget::XXOpenGlWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void XXOpenGlWidget::initializeGL()
{
    initializeOpenGLFunctions();
}

void XXOpenGlWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void XXOpenGlWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
