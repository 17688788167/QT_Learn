#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QVector>
#include "actor.h"
#include "data.h"
#include <QTimer>
#include <QTime>
#include "camera.h"
#include <QPoint>
#include <QMouseEvent>

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
    QVector<Actor*> LightVector;
    int ActorNum;
    QTime StartTime;
    float CurrentTime;
    float lastTime;
    float deltaTime;
    float ratio=0.5f;
    QPoint deltaPos;
    QPoint lastPos;
    bool isCanUseMouseMove=false;
    int8_t keyboard=0;
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);



signals:

public slots:
    void on_timeout();
private:
    EShape  m_shape;
    QOpenGLShaderProgram m_shader;
    QOpenGLTexture* m_texture1;

    QOpenGLShaderProgram shaderProgram;
    unsigned int VAO,VBO,EBO;
    QOpenGLTexture * textureWall;
    QOpenGLTexture * textureSmile;

    bool isMousePressed;
    QTimer timer;
    Camera m_camera;

    QOpenGLTexture * m_diffuseTex;
    QOpenGLTexture * m_specularTex;
    QOpenGLTexture * m_emissionTex;
};

#endif // MYOPENGLWIDGET_H
