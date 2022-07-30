#include "myopenglwidget.h"

#include "QDebug"


constexpr float Data::verticesAndTexCoords[];


//0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
//0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
//-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
//-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left

unsigned int indices[] = { // note that we start from 0!
                           0, 1, 3, // first triangle
                           1, 2, 3 // second triangle
                         };

MyOpenglWidget::MyOpenglWidget(QWidget *parent) : QOpenGLWidget(parent)
{

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

    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteVertexArrays(1,&VAO);

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

void MyOpenglWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_shape=Rect;
    Actor* actor1=new Actor(1,0,0,":/shaders/shapes.vs",":/shaders/shapes.fs",":/iamge/wall.jpg");
    ActorVector.push_back(actor1);

    Actor* actor2=new Actor(1,0.5f,0.5f,":/shaders/shapes.vs",":/shaders/shapes1.fs",":/iamge/wall.jpg");
    ActorVector.push_back(actor2);


    textureWall=new QOpenGLTexture(QImage(":/iamge/wall.jpg").mirrored());
    textureSmile=new QOpenGLTexture(QImage(":/iamge/awesomeface.png").mirrored());
     ActorNum=ActorVector.size();
     for (int i=0;i<ActorNum;++i)
     {
         glGenVertexArrays(1, &ActorVector[i]->glData.VAO);
         glGenBuffers(1, &ActorVector[i]->glData.VBO);

         glBindVertexArray(ActorVector[i]->glData.VAO);
         glBindBuffer(GL_ARRAY_BUFFER, ActorVector[i]->glData.VBO);

         //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
         glBufferData(GL_ARRAY_BUFFER, ActorVector[i]->ModelVerticesSizeof,ActorVector[i]->ModelVertices, GL_STATIC_DRAW);
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
         glEnableVertexAttribArray(0);

         glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
         //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)3);
         glEnableVertexAttribArray(1);

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
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //int ActorNum=ActorVector.size();
    float borderColor[]={0.2f,0.3f,0.3f,1.0f};

    switch (m_shape) {
    case Rect:
        for(int i=0;i<ActorNum;++i)
        {
//            ActorVector[i]->m_texture->bind(0);
//            ActorVector[i]->m_texture1->bind(1);
            ActorVector[i]->BindTexture();
            ActorVector[i]->m_shader.bind();


            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
            glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,borderColor);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


            glBindVertexArray(ActorVector[i]->glData.VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }



        break;
    default:
        break;
    }
}
