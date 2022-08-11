#include "myopenglwidget.h"

#include "QDebug"
#include <QVector3D>
#include <QtMath>
#include <QDir>
#include <iostream>
using namespace  std ;

QVector3D lightPos(1.2f, 1.0f, 2.0f);
QVector3D objectPos(-1.7f, 3.0f, -7.5f);
QVector3D objectScale(5.0f, 5.0f, 5.0f);
QVector3D lightColor(1.0f, 1.0f, 1.0f);
QVector3D lightDirection(1.0f, 1.0f, 1.0f);
QVector3D viewInitPos(0.0f,0.0f,5.0f);

float _near=0.1f;
float _far=1000.0f;
QMatrix4x4 model;
QMatrix4x4 view;
QMatrix4x4 projection;


const QVector<QVector3D> cubePositions= {
QVector3D( 0.0f, 0.0f, 0.0f),
QVector3D( 2.0f, 5.0f, -15.0f),
QVector3D(-1.5f, -2.2f, -2.5f),
QVector3D(-3.8f, -2.0f, -12.3f),
QVector3D( 2.4f, -0.4f, -3.5f),
QVector3D(-1.7f, 3.0f, -7.5f),
QVector3D( 1.3f, -2.0f, -2.5f),
QVector3D( 1.5f, 2.0f, -2.5f),
QVector3D( 1.5f, 0.2f, -1.5f),
QVector3D(-1.3f, 1.0f, -1.5f)
};

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

QVector3D pointLightPositions[] = {
    QVector3D( 0.7f, 0.2f, 2.0f),
    QVector3D( 2.3f, -3.3f, -4.0f),
    QVector3D(-4.0f, 2.0f, -12.0f),
    QVector3D( 0.0f, 0.0f, -3.0f)
};


QVector3D pointLightColorsDesert[] = {
    QVector3D(1.0f, 0.6f, 0.0f),
    QVector3D(1.0f, 0.0f, 0.0f),
    QVector3D(1.0f, 1.0, 0.0),
    QVector3D(0.2f, 0.2f, 1.0f)
};

QVector3D pointLightColorsFactory[] = {
    QVector3D(0.2f, 0.2f, 0.6f),
    QVector3D(0.3f, 0.3f, 0.7f),
    QVector3D(0.0f, 0.0f, 0.3f),
    QVector3D(0.4f, 0.4f, 0.4f)
};

QVector3D pointLightColorsHorror[] = {
    QVector3D(0.1f, 0.1f, 0.1f),
    QVector3D(0.1f, 0.1f, 0.1f),
    QVector3D(0.1f, 0.1f, 0.1f),
    QVector3D(0.3f, 0.1f, 0.1f)
};

QVector3D pointLightColorsBiochemicalLab[] = {
    QVector3D(1.0f, 0.6f, 0.0f),
    QVector3D(1.0f, 0.0f, 0.0f),
    QVector3D(1.0f, 1.0, 0.0),
    QVector3D(0.2f, 0.2f, 1.0f) }
;


MyOpenglWidget::MyOpenglWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    //激活键盘鼠标事件
    setFocusPolicy(Qt::StrongFocus);

    setMouseTracking(true);

    SetEnvironmentType(EnvironmentSettingDialog::EnvironmentType::DESERT);
    connect(&timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
    timer.start(10);
}

MyOpenglWidget::~MyOpenglWidget()
{

    makeCurrent();

    if(m_CubeMesh)
    {
        delete m_CubeMesh;
        m_CubeMesh=nullptr;
    }
    if(m_PlaneMesh)
    {
        delete m_PlaneMesh;
        m_PlaneMesh=nullptr;
    }

    if(m_light)
    {
        delete m_light;
        m_light=nullptr;
    }

    foreach(auto modelinfo,m_models)
    {
        delete modelinfo._model;
    }
    m_models.empty();

    doneCurrent();
}

void MyOpenglWidget::drawShape(EShape shape)
{
    m_shape=shape;

    //如果需要从paintGL（）以外的位置触发重新绘制（典型示例是使用计时器设置场景动画），则应调用widget的update（）函数来安排更新。

    update();
}

void MyOpenglWidget::setWireFrame(bool wireFrame)
{
    //如果需要从除了initializeGL()，paintGL（）、resizeGL（）其他位置调用标准OpenGL API函数，则必须首先调用makeCurrent();
    makeCurrent();
    if(wireFrame)
    {
        //线框模式
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }
    else
    {
        //填充模式
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }

    update();

}

void MyOpenglWidget::LoadModel(string path)
{

    makeCurrent();
    static int i=0;
    Model* m_model=new Model(m_glfuns,path.c_str());

    QVector3D modelPostion=m_camera.Position+m_camera.Front*20.0f-QVector3D(0.0f,m_model->getModelHeight()*0.5,0.0f) ;

    m_models["张三"+QString::number(i++)]=FModelInfo(m_model,modelPostion);
    doneCurrent();

}
QVector3D* pointLightColor;
void MyOpenglWidget::SetEnvironmentType(EnvironmentSettingDialog::EnvironmentType type)
{
    m_type=type;

    switch (type) {
    case EnvironmentSettingDialog::EnvironmentType::DESERT:
        pointLightColor=pointLightColorsDesert;
        ClearColor=QVector3D(0.75f, 0.52f, 0.3f);
        DirLight_ambient=QVector3D(0.3f, 0.7f, 0.5f)*2;
        DirLight_diffuse=QVector3D(0.7f, 0.42f, 0.26f)*2;
        DirLight_dspecular=QVector3D(0.5f, 0.5f, 0.5f)*2;
        break;

    case EnvironmentSettingDialog::EnvironmentType::FACTORY:
        pointLightColor=pointLightColorsFactory;
        ClearColor=QVector3D(0.0f, 0.0f, 0.0f);
        DirLight_ambient=QVector3D(0.05f, 0.05f, 0.1f);
        DirLight_diffuse=QVector3D(0.2f, 0.2f, 0.7f);
        DirLight_dspecular=QVector3D(0.7f, 0.7f, 0.7f);

        break;
    case EnvironmentSettingDialog::EnvironmentType::BIOCHEMICALLAB:
        pointLightColor=pointLightColorsBiochemicalLab;
        ClearColor=QVector3D(0.0f, 0.0f, 0.0f);
        DirLight_ambient=QVector3D(0.0f, 0.0f, 0.0f);
        DirLight_diffuse=QVector3D(0.05f, 0.05f, 0.05f);
        DirLight_dspecular=QVector3D(0.2f, 0.2f, 0.2f);

        break;
    case EnvironmentSettingDialog::EnvironmentType::HORROR:
        pointLightColor=pointLightColorsHorror;
        ClearColor=QVector3D(0.9f, 0.9f, 0.9f);
        DirLight_ambient=QVector3D(0.5f, 0.5f, 0.5f);
        DirLight_diffuse=QVector3D(1.0f, 1.0f, 1.0f);
        DirLight_dspecular=QVector3D(1.0f, 1.0f, 1.0f);

        break;

    default:
        break;
    }
}

void MyOpenglWidget::setType(const EnvironmentSettingDialog::EnvironmentType &type)
{
    m_type=type;
}



const float PI=3.1415926f;


void MyOpenglWidget::initializeGL()
{


    initializeOpenGLFunctions();
    //开始计时
    StartTime.start();


    //开启透明度
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    //开启深度
    glEnable(GL_DEPTH_TEST);
    m_shape=Rect;

    bool success;

    m_SingleColorShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shader/light.vert");
    m_SingleColorShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shader/singleColor.frag");
    success=m_SingleColorShaderProgram.link();
    if(!success) qDebug()<<"ERR:"<<m_SingleColorShaderProgram.log();

    m_ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shader/object.vert");
    m_ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shader/object.frag");
    success=m_ShaderProgram.link();
    if(!success) qDebug()<<"ERR:"<<m_ShaderProgram.log();

    m_diffuseTex=new QOpenGLTexture(QImage(":/iamge/wall.jpg").mirrored());
    m_specularTex=new QOpenGLTexture(QImage(":/iamge/container2_specular.png").mirrored());
    m_grassTex =new QOpenGLTexture(QImage(":/iamge/grass.png").mirrored());
    m_ShaderProgram.bind();

    m_LightShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shader/light.vert");
    m_LightShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shader/light.frag");
    success=m_LightShaderProgram.link();
    if(!success) qDebug()<<"ERR:"<<m_LightShaderProgram.log();

    m_glfuns=QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();

    m_PlaneMesh=processMesh(&Data::verticesAndTexCoords[0],6,m_specularTex->textureId());
    m_CubeMesh=processMesh(&Data::verticesAndTexCoords[0],36,m_diffuseTex->textureId());
    m_light=new LightBase(m_glfuns,lightColor);

    //shared_ptr<Mesh> m_shareptrMesh(m_CubeMesh);


    string path="../../environment/backpack/backpack.obj";
    cout<<"path:"<<path<<endl;
    //m_model=new Model(m_glfuns,path.c_str());
    //m_model=new Model(m_glfuns,"E:/Git/QT/QT_Learn/QT_Opengl_Depth/backpack/backpack.obj");
    //m_camera.SetCameraPosition(cameraPosInitByModel(m_model));

    Model* m_model=new Model(m_glfuns,path.c_str());

    QVector3D modelPostion=m_camera.Position+m_camera.Front*20.0f-QVector3D(0.0f,m_model->getModelHeight()*0.5,0.0f) ;

    m_models["张三"+QString::number(-1)]=FModelInfo(m_model,modelPostion);
    projection.setToIdentity();
    projection.perspective(m_camera.Zoom,(float)width()/height(),_near,_far);
}

void MyOpenglWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);

}



void MyOpenglWidget::paintGL()
{

    CurrentTime=StartTime.elapsed()/1000.0;
    deltaTime=CurrentTime-lastTime;
    lastTime=CurrentTime;

    model.setToIdentity();
    view.setToIdentity();




    for(int i=0;i<8;++i)
    {
        int temp=1 <<i;
        if(keyboard &temp)
        {
            if(i<6)
            {
                if(isCtrlCamera)
                {
                  m_camera.ProcessKeyboard((Camera_Movement)i,deltaTime);
                }
                else
                {
                    for(int i=0;i<selectedModels.size();++i)
                    {

                    }
                }
            }
            else if(i==6)
            {
                ratio+=0.5*deltaTime;
                ratio=ratio>1?1:ratio;
            }
            else if(i==7)
            {
                ratio-=0.5*deltaTime;
                ratio=ratio<0?0:ratio;
            }

        }

    }


    view=m_camera.GetViewMatrix();






    switch (m_shape) {
    case Rect:

        glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);

        glClearColor(ClearColor.x(),ClearColor.y(),ClearColor.z(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

        //参数为0禁止模板缓冲写入
    glStencilMask(0x00);

            m_ShaderProgram.bind();
          m_ShaderProgram.setUniformValue("projection", projection);
          m_ShaderProgram.setUniformValue("view", view);
          m_ShaderProgram.setUniformValue("viewPos",m_camera.Position);

                          //聚光灯
                         m_ShaderProgram.setUniformValue("spotlight.position",m_camera.Position);
                         m_ShaderProgram.setUniformValue("spotlight.direction",m_camera.Front);
                         m_ShaderProgram.setUniformValue("spotlight.cutOff",(float)cos(17.5f*PI/180));
                         m_ShaderProgram.setUniformValue("spotlight.cutOn",(float)cos(12.5f*PI/180));

                         m_ShaderProgram.setUniformValue("spotlight.ambient",lightColor *QVector3D(0.2f,0.2f,0.2f));
                         m_ShaderProgram.setUniformValue("spotlight.diffuse",lightColor *QVector3D(0.5f,0.5f,0.5f));
                         m_ShaderProgram.setUniformValue("spotlight.specular",1.0f, 1.0f, 1.0f);

                         m_ShaderProgram.setUniformValue("spotlight.constant",1.0f);
                         m_ShaderProgram.setUniformValue("spotlight.linear",0.09f);
                         m_ShaderProgram.setUniformValue("spotlight.quadratic",0.032f);

                          //方向光
                         m_ShaderProgram.setUniformValue("directlight.direction",-0.2f, -1.0f, -0.3f);
                         m_ShaderProgram.setUniformValue("directlight.ambient",DirLight_ambient);
                         m_ShaderProgram.setUniformValue("directlight.diffuse",DirLight_diffuse);
                         m_ShaderProgram.setUniformValue("directlight.specular", DirLight_dspecular);

                         //点光源

                                             QString iStr="pointlight["+QString::number(0)+"]."+"position";
                                            m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(),lightPos);

                                             iStr="pointlight["+QString::number(0)+"]."+"ambient";
                                            m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(),pointLightColor[0] *QVector3D(0.2f,0.2f,0.2f));
                                             iStr="pointlight["+QString::number(0)+"]."+"diffuse";
                                            m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(),pointLightColor[0] *QVector3D(0.5f,0.5f,0.5f));
                                             iStr="pointlight["+QString::number(0)+"]."+"specular";
                                            m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(),pointLightColor[0]);

                                             iStr="pointlight["+QString::number(0)+"]."+"constant";
                                            m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(),1.0f);
                                              iStr="pointlight["+QString::number(0)+"]."+"linear";
                                            m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(),0.09f);
                                              iStr="pointlight["+QString::number(0)+"]."+"quadratic";
                                            m_ShaderProgram.setUniformValue(iStr.toStdString().c_str(),0.032f);

                         //材质

                        m_ShaderProgram.setUniformValue("material.shininess", 32.0f);

                        //地板
                        if(m_PlaneMesh)
                        {
                            model.setToIdentity();
                            model.translate(0,-10,0);
                            model.rotate(90,QVector3D(1,0,0));

                            model.scale(10);
                            m_ShaderProgram.setUniformValue("model", model);
                            m_PlaneMesh->Draw(m_ShaderProgram);
                        }



          if(m_CubeMesh)
          {
              model.setToIdentity();
              model.translate(QVector3D(0,-3,0));
              m_ShaderProgram.setUniformValue("model", model);
//1.在绘制（需要添加轮廓的）物体之前，将模板函数设置为GL_ALWAYS，每当物体的片段被渲染时，将模板缓冲更新为1。
//glStencilFunc(GL_ALWAYS,1,0xFF);
//glStencilMask(0xFF);
            //2.第一次渲染物体
             m_CubeMesh->Draw(m_ShaderProgram);
//3.禁用模板写入以及深度测试
//glStencilFunc(GL_NOTEQUAL,1,0xFF);
//glStencilMask(0x00);
             //4.将物体缩放为1.1倍
            // model.scale(1.05f);
             //5.使用一个不同的片段着色器，输出一个单独的（边框）颜色。
            // m_SingleColorShaderProgram.bind();
            // m_SingleColorShaderProgram.setUniformValue("projection", projection);
            // m_SingleColorShaderProgram.setUniformValue("view", view);
            // m_SingleColorShaderProgram.setUniformValue("model", model);
             //6.再次绘制一个物体
            // m_CubeMesh->Draw(m_SingleColorShaderProgram);
             //m_SingleColorShaderProgram.release();
//7.再次启用模板写入和深度测试。
//glStencilMask(0xFF);
//glStencilFunc(GL_ALWAYS,1,0xFF);


          }


            foreach(auto modelInfo,m_models)
            {

                model.setToIdentity();
                model.translate(modelInfo._worldPos);
                model.rotate(modelInfo._pitch,QVector3D(1.0f,0.0f,0.0f));
                model.rotate(modelInfo._yaw,QVector3D(0.0f,1.0f,0.0f));
                model.rotate(modelInfo._roll,QVector3D(0.0f,0.0f,1.0f));

glStencilFunc(GL_ALWAYS,1,0xFF);
glStencilMask(0xFF);
                m_ShaderProgram.bind();
                m_ShaderProgram.setUniformValue("model", model);
                modelInfo._model->Draw(m_ShaderProgram);
                m_ShaderProgram.release();
glStencilFunc(GL_NOTEQUAL,1,0xFF);
glStencilMask(0x00);

//float xOffset= modelInfo._model->getModelWidth()/2.0f;
//float yOffset= modelInfo._model->getModelWidth()/2.0f;
                model.translate(modelInfo._model->getCenterPoint());
                model.scale(1.05f);

                model.translate(-modelInfo._model->getCenterPoint());
                m_SingleColorShaderProgram.bind();
                m_SingleColorShaderProgram.setUniformValue("projection", projection);
                m_SingleColorShaderProgram.setUniformValue("view", view);
                m_SingleColorShaderProgram.setUniformValue("model", model);
                modelInfo._model->Draw(m_SingleColorShaderProgram);
                m_SingleColorShaderProgram.release();
glStencilFunc(GL_ALWAYS,1,0xFF);
glStencilMask(0xFF);



                if(modelInfo._isSelected)
                {
                    m_LightShaderProgram.bind();
                    m_LightShaderProgram.setUniformValue("projection", projection);
                    m_LightShaderProgram.setUniformValue("view", view);
                    m_LightShaderProgram.setUniformValue("model", model);
                    modelInfo._model->DrawBox(m_LightShaderProgram);
                }

            }




          m_LightShaderProgram.bind();
          model.setToIdentity();
          model.translate(lightPos);
          model.rotate(1.0f, 1.0f, 1.0f, 0.5f);
          model.scale(0.2f);
          m_LightShaderProgram.setUniformValue("model", model);
          m_LightShaderProgram.setUniformValue("projection", projection);
          m_LightShaderProgram.setUniformValue("view", view);
          m_light->Draw(m_LightShaderProgram);
          m_LightShaderProgram.release();
        break;
    }
}
#include<QKeyEvent>
void MyOpenglWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:

    keyboard|= 1<<6;
    break;
    case Qt::Key_Down:
    keyboard|= 1<<7;

    break;

    case Qt::Key_W:
        keyboard|= 1<<2;
        break;
    case Qt::Key_S:
        keyboard|= 1<<3;
        break;
    case Qt::Key_D:
        keyboard|= 1<<4;
        break;
    case Qt::Key_A:
        keyboard|= 1<<5;
        break;
    case Qt::Key_R:
        m_camera.ResetCamera();
        break;

    }

    //ActorVector[0]->m_shader.bind();
    //ActorVector[0]->m_shader.setUniformValue("ratio",ratio);

    update();
}


void MyOpenglWidget::keyReleaseEvent(QKeyEvent *event)
{
    int Temp;
    switch(event->key())
    {
    case Qt::Key_Up:
        Temp=1<<6;
        Temp = ~Temp;
        keyboard &=Temp;
    break;
    case Qt::Key_Down:
        Temp=1<<7;
        Temp = ~Temp;
        keyboard &=Temp;
    break;


    case Qt::Key_W:
        Temp=1<<2;
        Temp = ~Temp;
        keyboard &=Temp;
        break;
    case Qt::Key_S:
        Temp=1<<3;
        Temp = ~Temp;
        keyboard &=Temp;
        break;
    case Qt::Key_D:
        Temp=1<<4;
        Temp = ~Temp;
        keyboard &=Temp;
        break;
    case Qt::Key_A:
        Temp=1<<5;
        Temp = ~Temp;
        keyboard &=Temp;
        break;
    }

    update();
}

void MyOpenglWidget::mousePressEvent(QMouseEvent *event)
{

    makeCurrent();
    if(event->button()&Qt::LeftButton)
    {
          keyboard|= 1;
         //qDebug()<<"鼠标单击:"<<event->pos().x()<<" "<<event->pos().y();
          QVector3D ClickWorldPos= QVector3D( worldPosFromViewPort(event->pos().x(),event->pos().y()));
          mousePickingPos(ClickWorldPos);
            isCtrlCamera=true;
            selectedModels.empty();
          for(auto iter=m_models.begin();iter!=m_models.end();++iter)
          {
              FModelInfo* modelinfo=&iter.value();
              float r=std::max(modelinfo->_model->getModelHeight()*0.5f,modelinfo->_model->getModelWidth()*0.5f);
              float distance=modelinfo->getCenterPoint().distanceToPoint(ClickWorldPos);
              modelinfo->_isSelected=distance<r;
              qDebug()<<"r:"<<r
                     <<" distance:"<<distance
                       <<" "<<modelinfo->_isSelected;
              if(modelinfo->_isSelected)
              {
                 selectedModels.push_back(modelinfo->_model);
                 isCtrlCamera=false;
              }
              update();
          }
    }
    else if(event->button()&Qt::RightButton)
    {
         keyboard|= 1<<1;
    }
    isMousePressed=true;






   doneCurrent();


}

void MyOpenglWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int Temp;
    if(event->button()&Qt::LeftButton)
    {
        Temp=~1;
        keyboard &=Temp;
    }
    else if(event->button()&Qt::RightButton)
    {
        Temp=~(1<<1);
        keyboard &=Temp;
    }
    isMousePressed=false;
    isCanUseMouseMove=false;
}


void MyOpenglWidget::mouseMoveEvent(QMouseEvent *event)
{

    if(!isMousePressed)
        return;
    //static QPoint lastPos(width()/2,height()/2);
    auto currentPos=event->pos();
    deltaPos=currentPos-lastPos;
    lastPos=currentPos;
    if(isCanUseMouseMove)
    {
        if(isCtrlCamera)
        m_camera.ProcessMouseMovement(deltaPos.x(),-deltaPos.y());
        else
        {
            for(int i=0;i<selectedModels.size();++i)
            {
                //实现拖拽模型,很简单,以后有空再做
            }
        }
        update();
    }

    isCanUseMouseMove=true;
}

void MyOpenglWidget::wheelEvent(QWheelEvent *event)
{
    m_camera.ProcessMouseScroll(event->angleDelta().y()/120);
    qDebug()<<event->angleDelta().y();
    update();
}

void MyOpenglWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
//    qDebug()<<"鼠标双击:"<<event->pos().x()<<" "<<event->pos().y();
//   // QVector3D ClickWorldPos= QVector3D( worldPosFromViewPort(event->pos().x(),event->pos().y()));
//    foreach(auto modelinfo,m_models)
//    {
//        float r=std::max(modelinfo._model->getModelHeight()*0.5f,modelinfo._model->getModelWidth()*0.5f);
//        float distance=ClickWorldPos.distanceToPoint(modelinfo._worldPos);
//        modelinfo._isSelected=distance<r;
//        qDebug()<<"r:"<<r
//               <<" distance:"<<distance;

//    }


}

void MyOpenglWidget::on_timeout()
{
    update();
}

Mesh * MyOpenglWidget::processMesh()
{
    vector<Vertex> _vertices(36);
    vector<unsigned int> _indices;
    vector<Texture> _textures;
    //因为数组vertices和结构体_vertices表示的数据都是一致的，切内存都是连续的，所以可以直接将数据的数据复制给结构体
    memcpy(&_vertices[0],vertices,sizeof(vertices));

    for(int i=0;i<36;i++)
    {
        _indices.push_back(i);
    }

    Texture tex;
    tex.id=m_diffuseTex->textureId();
    tex.type="texture_diffuse";
    _textures.push_back(tex);
    tex.id=m_specularTex->textureId();
    tex.type="texture_specular";
    _textures.push_back(tex);

    return new Mesh(m_glfuns,_vertices,_indices,_textures);
}

Mesh *MyOpenglWidget::processMesh(const float *vertices, int size, unsigned int textureId)
{
    vector<Vertex> _vertices;
    vector<unsigned int> _indices;
    vector<Texture> _textures;

    for(int i=0;i<size;i++)
    {
        Vertex vert;
        vert.Position[0]=vertices[i*5+0];
        vert.Position[1]=vertices[i*5+1];
        vert.Position[2]=vertices[i*5+2];

        vert.TexCoords[0]=vertices[i*5+3];
        vert.TexCoords[1]=vertices[i*5+4];

        _vertices.push_back(vert);
        _indices.push_back(i);
    }

    Texture tex;
    tex.id=textureId;
    tex.type="texture_diffuse";
    _textures.push_back(tex);

    return new Mesh(m_glfuns,_vertices,_indices,_textures);
}

QVector3D MyOpenglWidget::cameraPosInitByModel(Model *model)
{
    qDebug()<<model->getModelHeight();
    return viewInitPos*model->getModelHeight()*0.5f;
}

QVector4D MyOpenglWidget::worldPosFromViewPort(int posX, int posY)
{
    qDebug()<<"鼠标:"<<posX<<" "<<posY;
    float winZ;

    glReadPixels(posX,this->height()-posY,1,1,
                GL_DEPTH_COMPONENT,GL_FLOAT,&winZ );

      //将屏幕坐标x（0，width）映射到标准坐标空间（-1，1）
    float x=2.0f*posX/this->width()-1.0f;
     //将屏幕坐标y（0，height）映射到标准坐标空间（1，-1）
    float y=1.0f-2.0f*posY/this->height();
    //将上式算出的深度值winZ（0，1）映射到标准坐标空间（-1，1）
    float z=winZ*2.0f-1.0f;
  float w=(2.0f*_near*_far)/(_far+_near-z*(_far-_near));

  QVector4D worldPositon(x,y,z,1.0f);
  worldPositon*=w;
  worldPositon=view.inverted()*projection.inverted()*worldPositon;

  qDebug()<<"x:"<<worldPositon.x()
           <<"y:"<<worldPositon.y()
           << "z:"<<worldPositon.z()
            << "w:"<<worldPositon.w();

           qDebug()<<"winZ"<<winZ;

           return worldPositon;

}
