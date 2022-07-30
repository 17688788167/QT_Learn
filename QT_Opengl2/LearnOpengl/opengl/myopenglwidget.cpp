#include "myopenglwidget.h"

#include "QDebug"


constexpr float Data::verticesAndTexCoords[];


const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n" "void main()\n"
                                 "{\n"
                                 " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" "}\n\0";

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



        delete ActorVector[i];
    }
    ActorVector.empty();

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
    Actor* actor1=new Actor(1,0,0);
    ActorVector.push_back(actor1);
    Actor* actor2=new Actor(1,0.5f,0.5f);
    ActorVector.push_back(actor2);


     ActorNum=ActorVector.size();
     for (int i=0;i<ActorNum;++i)
     {
         glGenVertexArrays(1, &ActorVector[i]->glData.VAO);
         glGenBuffers(1, &ActorVector[i]->glData.VBO);

         glBindVertexArray(ActorVector[i]->glData.VAO);
         glBindBuffer(GL_ARRAY_BUFFER, ActorVector[i]->glData.VBO);

         glBufferData(GL_ARRAY_BUFFER, sizeof(Data::verticesAndTexCoords), Data::verticesAndTexCoords, GL_STATIC_DRAW);
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
         glEnableVertexAttribArray(0);


         glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)3);
         glEnableVertexAttribArray(1);
     }



}

void MyOpenglWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void MyOpenglWidget::paintGL()
{
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //int ActorNum=ActorVector.size();


    switch (m_shape) {
    case Rect:
        for(int i=0;i<ActorNum;++i)
        {
            glBindVertexArray(ActorVector[i]->glData.VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);

        }



        break;
    default:
        break;
    }





}
