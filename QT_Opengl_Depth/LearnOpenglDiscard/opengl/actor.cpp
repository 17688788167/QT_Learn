#include "actor.h"
#include <QDebug>
#include <QImage>
#include <iostream>
#include "MyOpenglWidget.h"
using namespace std;


constexpr float Data::verticesAndTexCoords[];


Actor::Actor( MyOpenglWidget*openGLWidget,const QString&VertexCodeFile,const QString&FragmentCodeFile)
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

void Actor::Rotate()
{
    m_shader.bind();
    model.rotate(0.5f,1.0f, 5.0f, 0.5f);
    m_shader.setUniformValue("model",model);
    m_openGLWidget->update();
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
