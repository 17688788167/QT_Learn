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
#include "environmentsettingdialog.h"
#include "mesh.h"
#include "model.h"
#include "lightbase.h"
#include "model/lightbase.h"

class Light;
class MyOpenglWidget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit MyOpenglWidget(QWidget *parent = nullptr);
    ~MyOpenglWidget();

    void drawShape(EShape shape);
    void setWireFrame(bool wireFrame);

    void LoadModel(string path);

    void SetEnvironmentType(EnvironmentSettingDialog::EnvironmentType type);
    EnvironmentSettingDialog::EnvironmentType m_type;
    void setType(const EnvironmentSettingDialog::EnvironmentType & type);

    EnvironmentSettingDialog::EnvironmentType getType()const
    {
        return m_type;
    }

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


    QVector3D ClearColor;
    QVector3D DirLight_ambient;
    QVector3D DirLight_diffuse;
    QVector3D DirLight_dspecular;
Camera m_camera;

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
    void mousePickingPos(const QVector4D& pos);
public slots:
    void on_timeout();
private:
    EShape  m_shape;
    QOpenGLShaderProgram m_ShaderProgram;
    QOpenGLTexture* m_texture1;

    QOpenGLShaderProgram shaderProgram;
    QOpenGLShaderProgram m_LightShaderProgram;
    unsigned int VAO,VBO,EBO;
    QOpenGLTexture * textureWall;
    QOpenGLTexture * textureSmile;

    bool isMousePressed;
    QTimer timer;


    QOpenGLTexture * m_diffuseTex;
    QOpenGLTexture * m_specularTex;
    QOpenGLTexture * m_emissionTex;
    QOpenGLFunctions_3_3_Core * m_glfuns;

    Mesh* m_mesh;
    Mesh* m_CubeMesh;
    Mesh* m_PlaneMesh;
    Model* m_model=NULL;

    LightBase* m_light;

    Mesh* processMesh();
    Mesh* processMesh(const float *vertices,int size,unsigned int textureId);
    QVector3D cameraPosInitByModel(Model *model);

    QVector4D worldPosFromViewPort(int posX,int posY);
};

#endif // MYOPENGLWIDGET_H
