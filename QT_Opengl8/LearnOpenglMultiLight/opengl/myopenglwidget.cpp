#include "myopenglwidget.h"

#include "QDebug"
#include <QVector3D>
#include <QtMath>

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


//QVector3D pointLightColors[] = {
//    QVector3D(1.0f, 1.0f, 0.0f),
//    QVector3D(0.3f, 1.0f, 0.7f),
//    QVector3D(0.0f, 0.0f, 0.3f),
//    QVector3D(0.4f, 0.4f, 0.4f)
//};

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

    SetEnvironmentType(EnvironmentSettingDialog::EnvironmentType::BIOCHEMICALLAB);
    connect(&timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
    timer.start(10);
}

MyOpenglWidget::~MyOpenglWidget()
{

    makeCurrent();
    for(int i=0;i<ActorNum;++i)
    {
      glDeleteVertexArrays(1,&ActorVector[i]->glData.VAO);
      glDeleteBuffers(1,&ActorVector[i]->glData.VBO);
     // glDeleteShader(ActorVector[i]->m_shader);

      delete ActorVector[i];
    }
    ActorVector.empty();

    if(m_texture1)
    {
       delete m_texture1;
        m_texture1=nullptr;
    }


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
QVector3D* pointLightColor;
void MyOpenglWidget::SetEnvironmentType(EnvironmentSettingDialog::EnvironmentType type)
{
    m_type=type;

    switch (type) {
    case EnvironmentSettingDialog::EnvironmentType::DESERT:
        pointLightColor=pointLightColorsDesert;
        ClearColor=QVector3D(0.75f, 0.52f, 0.3f);
        DirLight_ambient=QVector3D(0.3f, 0.24f, 0.14f);
        DirLight_diffuse=QVector3D(0.7f, 0.42f, 0.26f);
        DirLight_dspecular=QVector3D(0.5f, 0.5f, 0.5f);
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
        DirLight_diffuse=QVector3D(0.05f, 0.05f, 0.05);
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
QVector3D lightPos(1.2f, 1.0f, 2.0f);
QVector3D objectPos(-1.7f, 3.0f, -7.5f);
QVector3D objectScale(5.0f, 5.0f, 5.0f);
QVector3D lightColor(1.0f, 1.0f, 1.0f);
QVector3D lightDirection(1.0f, 1.0f, 1.0f);
const float PI=3.1415926;


void MyOpenglWidget::initializeGL()
{
    initializeOpenGLFunctions();
    //开始计时
    StartTime.start();

//    ClearColor=QVector3D(0.1f, 0.1f, 0.1f);
//    DirLight_ambient=QVector3D(0.75,0.52,0.3);
//    DirLight_diffuse=QVector3D(0.75,0.52,0.3);
//    DirLight_dspecular=QVector3D(0.75,0.52,0.3);


    //pointLightColor =pointLightColorsDesert;

    //开启透明度
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    //开启深度
    glEnable(GL_DEPTH_TEST);

    textureWall=new QOpenGLTexture(QImage(":/iamge/wall.jpg").mirrored());
    textureSmile=new QOpenGLTexture(QImage(":/iamge/awesomeface.png").mirrored());

    qDebug()<<"11111111111";
    m_shape=Rect;

          for(unsigned int i=0;i< 4;++i)
          {
              Actor* Light=new Actor(this,":/shader/light.vert",":/shader/light.frag");
              Light->InitModel(QVector3D(0.3,0.3,0.3),pointLightPositions[i],0,QVector3D(0,0,1));
              LightVector.push_back(Light);

              glGenVertexArrays(1, &Light->glData.VAO);
              glGenBuffers(1, &Light->glData.VBO);

              glBindVertexArray(Light->glData.VAO);
              glBindBuffer(GL_ARRAY_BUFFER, Light->glData.VBO);

              glBufferData(GL_ARRAY_BUFFER,sizeof(vertices) ,vertices, GL_STATIC_DRAW);
              glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
              glEnableVertexAttribArray(0);

              glBindVertexArray(0);
              glBindBuffer(GL_ARRAY_BUFFER, 0);
          }

          m_diffuseTex=new QOpenGLTexture(QImage(":/iamge/container2.png").mirrored());
          m_specularTex=new QOpenGLTexture(QImage(":/iamge/container2_specular.png").mirrored());
          m_emissionTex=new QOpenGLTexture(QImage(":/iamge/matrix.jpg").mirrored());

          ActorNum=cubePositions.size();
          for(int i=0;i<ActorNum;++i)
          {
              Actor *actorTemp=new Actor(this,":/shader/object.vert",":/shader/object.frag");
              actorTemp->InitModel(QVector3D(1,1,1),cubePositions[i],20.0*i,QVector3D(1.0f,0.3f,0.5f));
              ActorVector.push_back(actorTemp);

              glGenVertexArrays(1, &actorTemp->glData.VAO);
              glGenBuffers(1, &actorTemp->glData.VBO);

              glBindVertexArray(actorTemp->glData.VAO);
              glBindBuffer(GL_ARRAY_BUFFER, actorTemp->glData.VBO);

              //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
              glBufferData(GL_ARRAY_BUFFER,sizeof(vertices) ,vertices, GL_STATIC_DRAW);
              glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
              glEnableVertexAttribArray(0);

              glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
              glEnableVertexAttribArray(1);

              glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
              glEnableVertexAttribArray(2);
              actorTemp->m_shader.bind();
              actorTemp->m_shader.setUniformValue("material.diffuse",0);
              actorTemp->m_shader.setUniformValue("material.specular",1);
              actorTemp->m_shader.setUniformValue("material.emission",2);
              actorTemp->m_shader.setUniformValue("material.shininess", 32.0f);
              glBindVertexArray(0);
              glBindBuffer(GL_ARRAY_BUFFER, 0);
          }
}

void MyOpenglWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
    //glViewport(0,0,w,h);
}

void MyOpenglWidget::paintGL()
{

    CurrentTime=StartTime.elapsed()/1000.0;
    deltaTime=CurrentTime-lastTime;
    lastTime=CurrentTime;

    QMatrix4x4 view;
    QMatrix4x4 projection;


    for(int i=0;i<8;++i)
    {
        int temp=1 <<i;
        if(keyboard &temp)
        {
            if(i<6)
            m_camera.ProcessKeyboard((Camera_Movement)i,deltaTime);
            else if(i==6)
            {
                ratio+=0.5*deltaTime;
                ratio=ratio>1?1:ratio;
                ActorVector[0]->AddActorLocation(deltaTime*2*QVector3D(0,0,1));
            }
            else if(i==7)
            {
                ratio-=0.5*deltaTime;
                ratio=ratio<0?0:ratio;
                ActorVector[0]->AddActorLocation(-deltaTime*2*QVector3D(0,0,1));
            }
            //qDebug()<<ratio;
        }

    }

    //model.rotate(CurrentTime*45,1,1,0);
    //view.translate(0,0,-3);

    view=m_camera.GetViewMatrix();
    projection.perspective(m_camera.Zoom,(float)width()/height(),0.1,1000);

    glClearColor(ClearColor.x(),ClearColor.y(),ClearColor.z(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    switch (m_shape) {
    case Rect:

        lightDirection.setX(sin(CurrentTime * 2.0f));
        lightDirection.setY(sin(CurrentTime * 0.7f));
        lightDirection.setZ(sin(CurrentTime * 1.3f));

        //qDebug()<<CurrentTime;
        for(int i=0;i<ActorNum;++i)
        {
            ActorVector[i]->m_shader.bind();
            ActorVector[i]->m_shader.setUniformValue("view",view);
            ActorVector[i]->m_shader.setUniformValue("projection",projection);


                //聚光灯
                ActorVector[i]->m_shader.setUniformValue("spotlight.position",m_camera.Position);
                ActorVector[i]->m_shader.setUniformValue("spotlight.direction",m_camera.Front);
                ActorVector[i]->m_shader.setUniformValue("spotlight.cutOff",(float)cos(17.5f*PI/180));
                ActorVector[i]->m_shader.setUniformValue("spotlight.cutOn",(float)cos(12.5f*PI/180));

                ActorVector[i]->m_shader.setUniformValue("spotlight.ambient",lightColor *QVector3D(0.2,0.2,0.2));
                ActorVector[i]->m_shader.setUniformValue("spotlight.diffuse",lightColor *QVector3D(0.5,0.5,0.5));
                ActorVector[i]->m_shader.setUniformValue("spotlight.specular",1.0f, 1.0f, 1.0f);

                ActorVector[i]->m_shader.setUniformValue("spotlight.constant",1.0f);
                ActorVector[i]->m_shader.setUniformValue("spotlight.linear",0.09f);
                ActorVector[i]->m_shader.setUniformValue("spotlight.quadratic",0.032f);

                //方向光
                ActorVector[i]->m_shader.setUniformValue("directlight.direction",-0.2f, -1.0f, -0.3f);
                ActorVector[i]->m_shader.setUniformValue("directlight.ambient",DirLight_ambient);
                ActorVector[i]->m_shader.setUniformValue("directlight.diffuse",DirLight_diffuse);
                ActorVector[i]->m_shader.setUniformValue("directlight.specular", DirLight_dspecular);


                //点光源

                for(int i=0;i<4;++i)
                {
                    QString iStr="pointlight["+QString::number(i)+"]."+"position";
                    ActorVector[i]->m_shader.setUniformValue(iStr.toStdString().c_str(),pointLightPositions[i]);

                    iStr="pointlight["+QString::number(i)+"]."+"ambient";
                    ActorVector[i]->m_shader.setUniformValue(iStr.toStdString().c_str(),pointLightColor[i] *QVector3D(0.2,0.2,0.2));
                    iStr="pointlight["+QString::number(i)+"]."+"diffuse";
                    ActorVector[i]->m_shader.setUniformValue(iStr.toStdString().c_str(),pointLightColor[i] *QVector3D(0.5,0.5,0.5));
                    iStr="pointlight["+QString::number(i)+"]."+"specular";
                    ActorVector[i]->m_shader.setUniformValue(iStr.toStdString().c_str(),pointLightColor[i]);

                    iStr="pointlight["+QString::number(i)+"]."+"constant";
                    ActorVector[i]->m_shader.setUniformValue(iStr.toStdString().c_str(),1.0f);
                     iStr="pointlight["+QString::number(i)+"]."+"linear";
                    ActorVector[i]->m_shader.setUniformValue(iStr.toStdString().c_str(),0.09f);
                     iStr="pointlight["+QString::number(i)+"]."+"quadratic";
                    ActorVector[i]->m_shader.setUniformValue(iStr.toStdString().c_str(),0.032f);


                }




                ActorVector[i]->m_shader.setUniformValue("viewPos",m_camera.Position);


                m_diffuseTex->bind(0);
                m_specularTex->bind(1);
                m_emissionTex->bind(2);                

            glBindVertexArray(ActorVector[i]->glData.VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        for(unsigned int i=0;i<4;++i)
        {
            LightVector[i]->m_shader.bind();
            LightVector[i]->m_shader.setUniformValue("view",view);
            LightVector[i]->m_shader.setUniformValue("projection",projection);
            LightVector[i]->m_shader.setUniformValue("lightColor",pointLightColor[i]);
            glBindVertexArray(ActorVector[i]->glData.VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        break;
    default:
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

    ActorVector[0]->m_shader.bind();
    ActorVector[0]->m_shader.setUniformValue("ratio",ratio);

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
    if(event->button()==Qt::LeftButton)
    {
          keyboard|= 1;
    }
    else if(event->button()==Qt::RightButton)
    {
         keyboard|= 1<<1;
    }
    isMousePressed=true;
}

void MyOpenglWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int Temp;
    if(event->button()==Qt::LeftButton)
    {
        Temp=~1;
        keyboard &=Temp;
    }
    else if(event->button()==Qt::RightButton)
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
        m_camera.ProcessMouseMovement(deltaPos.x(),-deltaPos.y());
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

void MyOpenglWidget::on_timeout()
{
    update();
}
