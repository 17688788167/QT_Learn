#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QVector>
#include "actor.h"
#include "data.h"

class MyOpenglWidget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit MyOpenglWidget(QWidget *parent = nullptr);
    ~MyOpenglWidget();

    void drawShape(EShape shape);
    void setWireFrame(bool wireFrame);


    //QVector<FGLData*> GLDataVector;

    QVector<Actor*> ActorVector;
    int ActorNum;

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();


signals:

public slots:

private:
    EShape  m_shape;
    QOpenGLShaderProgram m_shader;
    QOpenGLTexture* m_texture1;

    QOpenGLShaderProgram shaderProgram;
    unsigned int VAO,VBO,EBO;
    QOpenGLTexture * textureWall;
    QOpenGLTexture * textureSmile;
};

#endif // MYOPENGLWIDGET_H
