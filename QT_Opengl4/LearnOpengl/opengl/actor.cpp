#include "actor.h"
#include <QDebug>
#include <QImage>
#include <iostream>
using namespace std;
Actor::Actor()
{

}

Actor::Actor(float Scale, float xOffset, float yOffset,const QString&VertexCodeFile,const QString&FragmentCodeFile,const QString&TextureFile)
{
    GenModelVerticesData(Scale,xOffset,yOffset);

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
    m_shader.setUniformValue("m_texture2",2);
    //m_texture->bind(0);



}

Actor::~Actor()
{
    if(ModelVertices)
    {
     delete[] ModelVertices;
     //ModelVertices=nullptr;
    }
    if(m_texture)
    {
        delete m_texture;
        m_texture=nullptr;
    }
}


void Actor::GenModelVerticesData(float Scale, float xOffset, float yOffset)
{
            ModelVerticesSizeof=sizeof(Data::verticesAndTexCoords);
            int num = ModelVerticesSizeof / sizeof(float);
            //ModelVertices = new float[num];
            for (int i = 0; i < num; ++i)
            {
                if (i%5<3)
                {
                  ModelVertices[i] =  Data::verticesAndTexCoords[i]*Scale;
                }

                if (i % 5 == 0)
                {
                    ModelVertices[i] += xOffset;
                    cout<<endl;
                    cout<<ModelVertices[i]<<" ";

                }
                else if (i % 5 == 1)
                {
                    ModelVertices[i] += yOffset;
                    cout<<ModelVertices[i]<<" ";
                }
                else
                {
                    ModelVertices[i] =  Data::verticesAndTexCoords[i];
                   cout<<ModelVertices[i]<<" ";
                }



            }
}

void Actor::DrawActor()
{

}

void Actor::BindTexture()
{
    m_texture->bind(0);
    m_texture1->bind(1);
    m_texture2->bind(2);

}
