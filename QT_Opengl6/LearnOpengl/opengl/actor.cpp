#include "actor.h"
#include <QDebug>
#include <QImage>
#include <iostream>
#include "MyOpenglWidget.h"
using namespace std;


constexpr float Data::verticesAndTexCoords[];
Actor::Actor()
{

}

Actor::Actor( MyOpenglWidget*openGLWidget,const QString&VertexCodeFile,const QString&FragmentCodeFile,const QString&TextureFile)
{


    m_openGLWidget=openGLWidget;



    //初始化着色器
   bool success;
   success= m_shader.addShaderFromSourceFile(QOpenGLShader::Vertex,VertexCodeFile);
   if(!success)
        qDebug()<<"打开顶点着色器失败:"<<m_shader.log();
   success= m_shader.addShaderFromSourceFile(QOpenGLShader::Fragment,FragmentCodeFile);
   if(!success)
        qDebug()<<"打开片段着色器失败:"<<m_shader.log();

    m_shader.link();


    //初始化纹理
    m_texture=new QOpenGLTexture(QImage(TextureFile).mirrored());
    m_texture1=new QOpenGLTexture(QImage(":/iamge/awesomeface.png").mirrored());
    m_texture2=new QOpenGLTexture(QImage(":/iamge/small.png").mirrored());

    m_shader.bind();
    m_shader.setUniformValue("m_Texture",0);
    m_shader.setUniformValue("m_Texture1",1);
    m_shader.setUniformValue("m_Texture2",2);


}

Actor::~Actor()
{
    if(ModelVertices)
    {
     delete ModelVertices;

     ModelVertices=nullptr;
    }
    if(m_texture)
    {
        delete m_texture;
        m_texture=nullptr;
    }
    if(scene)
    {
        delete scene;
        scene=nullptr;
    }
}


void Actor::GenModelVerticesData(float Scale, float xOffset, float yOffset,float zOffset)
{
            ModelVerticesSizeof=sizeof(Data::verticesAndTexCoords);
            int num = ModelVerticesSizeof / sizeof(float);
            ModelVertices = new float[num];
            for (int i = 0; i < num; ++i)
            {
                if (i%5<3)
                {
                  ModelVertices[i] =  Data::verticesAndTexCoords[i]*Scale;
                }

                if (i % 5 == 0)
                {
                    ModelVertices[i] += xOffset;
                    //cout<<endl;
                   // cout<<ModelVertices[i]<<" ";

                }
                else if (i % 5 == 1)
                {
                    ModelVertices[i] += yOffset;
                   // cout<<ModelVertices[i]<<" ";
                }
                else if(i%5==2)
                {
                   ModelVertices[i] += zOffset;
                }
                else
                {
                    ModelVertices[i] =  Data::verticesAndTexCoords[i];
                   //cout<<ModelVertices[i]<<" ";
                }
            }
}

void Actor::DrawActor()
{
    m_openGLWidget-> makeCurrent();
    glBindVertexArray(glData.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_openGLWidget->update();
}



void Actor::BindTexture()
{
    m_shader.bind();
    m_texture->bind(0);
    m_texture1->bind(1);
    m_texture2->bind(2);

    m_openGLWidget->update();

}

void Actor::InitModel(const QVector3D& Scale,const QVector3D& Position,float angle,const QVector3D& axis)
{
    this->Position=Position;
    this->Scale=Scale;
    this->Angle=angle;
    this->Axis=axis;
    UpdateModel();
}

void Actor::AddActorLocation(const QVector3D &LocOffset)
{
     this->Position+=LocOffset;
     model.translate(LocOffset);
     UpdateModel();
}

void Actor::UpdateModel()
{
    model.setToIdentity();
    model.translate(Position);
    model.rotate(Angle,Axis);
    model.scale(Scale);
    m_shader.bind();
    m_shader.setUniformValue("model",model);
    m_openGLWidget->update();
}
