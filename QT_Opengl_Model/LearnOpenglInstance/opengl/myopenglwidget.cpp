#include "myopenglwidget.h"

#include "QDebug"
#include <QVector3D>
#include <QtMath>
#define QMatrix4x4DataSize 64

QVector3D lightPos(1.2f, 1.0f, 2.0f);
QVector3D objectPos(-1.7f, 3.0f, -7.5f);
QVector3D objectScale(5.0f, 5.0f, 5.0f);
QVector3D lightColor(1.0f, 1.0f, 1.0f);
QVector3D lightDirection(1.0f, 1.0f, 1.0f);
QVector3D viewInitPos(0.0f,0.0f,5.0f);

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

    if(m_mesh)
    {
        delete m_mesh;
        m_mesh=nullptr;
    }
//    if(m_light)
//    {
//        delete m_light;
//        m_light=nullptr;
//    }
    if(m_model)
    {
        delete m_model;
        m_model=nullptr;
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

void MyOpenglWidget::LoadModel(string path)
{
    if(m_model)
    {
        delete m_model;
        m_model=nullptr;
    }
    makeCurrent();
    m_model=new Model(m_glfuns,path.c_str());
    m_camera.SetCameraPosition(cameraPosInitByModel(m_model));
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
    //glEnable(GL_PROGRAM_POINT_SIZE);

    //开启透明度
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    //开启深度
    glEnable(GL_DEPTH_TEST);
    m_shape=Rect;

    genShader(screenShaderProgram,":/shader/instanceArray.vert",":/shader/instanceArray.frag");
    genShader(showNormalShaderProgram,":/shader/displaynormal.vert",":/shader/displaynormal.frag",":/shader/displaynormal.geom");
    genShader(explodeShaderProgram,":/shader/explode.vert",":/shader/explode.frag",":/shader/explode.geom");
    genShader(geometryShaderProgram,":/shader/point.vert",":/shader/point.frag",":/shader/point.geom");
    genShader(m_ShaderProgram,":/shader/object.vert",":/shader/object.frag");
    genShader(m_LightShaderProgram,":/shader/light.vert",":/shader/light.frag");
    genShader(reflectionShaderProgram,":/shader/reflection.vert",":/shader/reflection.frag");

    m_diffuseTex=new QOpenGLTexture(QImage(":/iamge/container2.png").mirrored());
    m_specularTex=new QOpenGLTexture(QImage(":/iamge/container2_specular.png").mirrored());
    m_ShaderProgram.bind();



    m_glfuns=QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    m_mesh=processMesh();
    //m_lightMesh=processMesh(EMeshType::Light);
     m_light=new LightBase(m_glfuns,lightColor);
        reflectCube=new LightBase(m_glfuns,lightColor);
    cubeMesh=processMesh(&Data::verticesAndTexCoords[0],36,m_diffuseTex->textureId());
    genSkyBoxVAOandVBO();

    geometry=new Geometry(m_glfuns);
    screen=new Screen(m_glfuns,&screenShaderProgram);


    unsigned int uniformBlockIndexShowNormalShader  = glGetUniformBlockIndex(showNormalShaderProgram.programId(), "Matrices");
    unsigned int uniformBlockIndexExplodeShader  = glGetUniformBlockIndex(explodeShaderProgram.programId(), "Matrices");
    unsigned int uniformBlockIndexShader  = glGetUniformBlockIndex(m_ShaderProgram.programId(), "Matrices");
    unsigned int uniformBlockIndexlightShader  = glGetUniformBlockIndex(m_LightShaderProgram.programId(), "Matrices");
    unsigned int uniformBlockIndexreflectionShader  = glGetUniformBlockIndex(reflectionShaderProgram.programId(), "Matrices");
    unsigned int uniformBlockIndexskyShader  = glGetUniformBlockIndex(skyshaderProgram.programId(), "Matrices");

    glUniformBlockBinding(showNormalShaderProgram.programId(), uniformBlockIndexShowNormalShader, 0);
    glUniformBlockBinding(explodeShaderProgram.programId(), uniformBlockIndexExplodeShader, 0);
    glUniformBlockBinding(m_ShaderProgram.programId(),    uniformBlockIndexShader, 0);
    glUniformBlockBinding(m_LightShaderProgram.programId(),  uniformBlockIndexlightShader, 0);
    glUniformBlockBinding(reflectionShaderProgram.programId(),   uniformBlockIndexreflectionShader, 0);
    glUniformBlockBinding(skyshaderProgram.programId(), uniformBlockIndexskyShader, 0);


    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * QMatrix4x4DataSize, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * QMatrix4x4DataSize);

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

    QMatrix4x4 model;
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
                //ActorVector[0]->AddActorLocation(deltaTime*2*QVector3D(0,0,1));
            }
            else if(i==7)
            {
                ratio-=0.5*deltaTime;
                ratio=ratio<0?0:ratio;
                //ActorVector[0]->AddActorLocation(-deltaTime*2*QVector3D(0,0,1));
            }
            //qDebug()<<ratio;
        }

    }


    view=m_camera.GetViewMatrix();
    projection.perspective(m_camera.Zoom,(float)width()/height(),0.1f,1000);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, QMatrix4x4DataSize,  projection.constData());
    glBufferSubData(GL_UNIFORM_BUFFER, QMatrix4x4DataSize, QMatrix4x4DataSize, view.constData());

    glBindBuffer(GL_UNIFORM_BUFFER, 0);



    glClearColor(ClearColor.x(),ClearColor.y(),ClearColor.z(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    switch (m_shape) {
    case Rect:

            m_ShaderProgram.bind();

         // m_mesh->Draw(m_ShaderProgram,this);


         // model.rotate(CurrentTime*10, 1.0f, 1.0f, 0.5f);
          m_ShaderProgram.setUniformValue("viewPos",m_camera.Position);



                                            //m_ShaderProgram.setUniformValue("light.direction", -0.2f, -1.0f, -0.3f);


          glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);




          if(cubeMesh)
          {
              reflectionShaderProgram.bind();


              reflectionShaderProgram.setUniformValue("model", model);
              reflectionShaderProgram.setUniformValue("viewPos",m_camera.Position);

              reflectCube->Draw(reflectionShaderProgram);
             // cubeMesh->Draw(reflectionShaderProgram);

              //reflectionShaderProgram.setUniformValue("skybox",3);
              //skyTexture->bind(3);
              //glActiveTexture(GL_TEXTURE0+2);
             // glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture->textureId());

            // reflectionShaderProgram.release();
          }
            m_ShaderProgram.bind();
            setObjectShader();
             m_ShaderProgram.setUniformValue("model", model);
          if(m_model)
          {
                glActiveTexture(GL_TEXTURE15);
                glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture->textureId());
                m_ShaderProgram.setUniformValue("skybox",15);


                explodeShaderProgram.bind();
                explodeShaderProgram.setUniformValue("model", model);
                explodeShaderProgram.setUniformValue("time", CurrentTime);

                showNormalShaderProgram.bind();
                showNormalShaderProgram.setUniformValue("model",model);
                m_ShaderProgram.bind();
                m_model->Draw(m_ShaderProgram);
          }


          //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

           m_LightShaderProgram.bind();
           m_LightShaderProgram.setUniformValue("model", model);


           if(m_model)
           {
               m_model->DrawBox(m_LightShaderProgram);
           }

          model.setToIdentity();
          model.translate(lightPos);
          model.rotate(1.0f, 1.0f, 1.0f, 0.5f);
          model.scale(0.2f);
          m_LightShaderProgram.setUniformValue("model", model);
          //m_LightShaderProgram.setUniformValue("lightColor",pointLightColor[0]);
          //m_lightMesh->Draw(m_LightShaderProgram);
          m_light->Draw(m_LightShaderProgram);


          screen->Draw();
           // geometry->Draw(geometryShaderProgram);

          // draw skybox as last
          glDepthFunc(GL_LEQUAL); // 确保天空盒=1也能通过测试
          skyshaderProgram.bind();
          QMatrix4x4 skyboxView=view;// remove translation from the view matrix
          skyboxView.setColumn(3,QVector4D(0.0f,0.0f,0.0f,1.0f));
          skyshaderProgram.setUniformValue("skyView", skyboxView);
          // skybox cube
          glBindVertexArray(skyVAO);
          glActiveTexture(GL_TEXTURE0);
          glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture->textureId());

          //m_ShaderProgram.setUniformValue("skybox",3);
          glDrawArrays(GL_TRIANGLES, 0, 36);
          glBindVertexArray(0);
          glDepthFunc(GL_LESS); // set depth function back to default
          skyshaderProgram.release();

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

void MyOpenglWidget::genShader(QOpenGLShaderProgram &shader, const QString &vertFile, const QString &fragFile)
{

    bool success;
    shader.addShaderFromSourceFile(QOpenGLShader::Vertex,vertFile);
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment,fragFile);
    success=m_ShaderProgram.link();
    if(!success) qDebug()<<"ERR:"<<shader.log();
}

void MyOpenglWidget::genShader(QOpenGLShaderProgram &shader, const QString &vertFile, const QString &fragFile, const QString &geomFile)
{
    shader.addShaderFromSourceFile(QOpenGLShader::Geometry,geomFile);
    genShader(shader,vertFile,fragFile);
}

void MyOpenglWidget::setObjectShader()
{
    m_ShaderProgram.setUniformValue("light.ambient", 0.4f, 0.4f, 0.4f);
    m_ShaderProgram.setUniformValue("light.diffuse", 0.9f, 0.9f, 0.9f);
    m_ShaderProgram.setUniformValue("light.specular", 1.0f, 1.0f, 1.0f);


    //方向光
    m_ShaderProgram.setUniformValue("directlight.direction",-0.2f, -1.0f, -0.3f);
    m_ShaderProgram.setUniformValue("directlight.ambient",DirLight_ambient);
    m_ShaderProgram.setUniformValue("directlight.diffuse",DirLight_diffuse);
    m_ShaderProgram.setUniformValue("directlight.specular", DirLight_dspecular);

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
                                      m_ShaderProgram.setUniformValue("material.shininess", 32.0f);
}

void MyOpenglWidget::genSkyBoxVAOandVBO()
{
    genShader(skyshaderProgram,":/shader/skybox.vert",":/shader/skybox.frag");
    skyTexture=new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    QImage _right   = QImage(":/skybox/right.jpg").convertToFormat(QImage::Format_RGB888);
    QImage _left    = QImage(":/skybox/left.jpg").convertToFormat(QImage::Format_RGB888);
    QImage _top     = QImage(":/skybox/top.jpg").convertToFormat(QImage::Format_RGB888);
    QImage _bottom  = QImage(":/skybox/bottom.jpg").convertToFormat(QImage::Format_RGB888);
    QImage _front   = QImage(":/skybox/front.jpg").convertToFormat(QImage::Format_RGB888);
    QImage _back    = QImage(":/skybox/back.jpg").convertToFormat(QImage::Format_RGB888);
    skyTexture->setSize(_right.width(), _right.height());
    skyTexture->setFormat(QOpenGLTexture::RGBFormat);
    skyTexture->allocateStorage(QOpenGLTexture::RGB, QOpenGLTexture::UInt8);
    skyTexture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX,QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *)_right.bits());
    skyTexture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX,QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *)_left.bits());
    skyTexture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY,QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *)_top.bits());
    skyTexture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY,QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *)_bottom.bits());
    skyTexture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ,QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *)_front.bits());
    skyTexture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ,QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *)_back.bits());

    skyTexture->setMinificationFilter(QOpenGLTexture::Linear);     //纹理放大或缩小时，像素的取值方法 ，线性或就近抉择
    skyTexture->setMagnificationFilter(QOpenGLTexture::Linear);
    skyTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);   //设置纹理边缘的扩展方法
    skyTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
 //   skyTexture->setWrapMode(QOpenGLTexture::DirectionR, QOpenGLTexture::ClampToEdge);

    // skybox VAO
    glGenVertexArrays(1, &skyVAO);
    glGenBuffers(1, &skyVBO);
    glBindVertexArray(skyVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Data::skyboxVertices), &Data::skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}
