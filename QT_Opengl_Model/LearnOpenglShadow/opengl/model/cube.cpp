#include "cube.h"
#include "data.h"

void CubeActor::Draw(QOpenGLShaderProgram &shader)
{
    shader.bind();
    QMatrix4x4 model;
    model.setToIdentity();
    model.translate(1,3,1);
    model.rotate(45,1,1,1);

m_diffuse->bind(0);
m_specular->bind(1);

    //m_specular->bind(3);
   // shader.setUniformValue("textureTest",3);
    shader.setUniformValue("material.texture_diffuse1",0);
    shader.setUniformValue("material.texture_specular1",1);


    shader.setUniformValue("model",model);
    m_glFuns->glBindVertexArray(m_gldata.VAO);
    m_glFuns->glDrawArrays(GL_TRIANGLES, 0, 36);


     model.setToIdentity();
     model.translate(-3,1.0f,0);
     model.scale(1.5f);
     shader.setUniformValue("model",model);
     m_glFuns->glBindVertexArray(m_gldata.VAO);
     m_glFuns->glDrawArrays(GL_TRIANGLES, 0, 36);

    model.setToIdentity();
    model.translate(0,0.5f,0);

    shader.setUniformValue("model",model);
    m_glFuns->glBindVertexArray(m_gldata.VAO);
    m_glFuns->glDrawArrays(GL_TRIANGLES, 0, 36);

    model.setToIdentity();

    model.scale(20);
    shader.setUniformValue("model",model);

textureWall->bind(0);
textureWall->bind(1);
    m_glFuns->glBindVertexArray(m_gldata.VAO);
    m_glFuns->glDrawArrays(GL_TRIANGLES, 0, 36);


    model.setToIdentity();
    shader.setUniformValue("model",model);
    shader.release();
}

void CubeActor::setupMesh()
{
    m_glFuns->glEnable((GL_PROGRAM_POINT_SIZE));
    //创建VBO，VAO，EBO对象,并赋予id
    m_glFuns->glGenVertexArrays(1,&m_gldata.VAO);
    m_glFuns->glGenBuffers(1, &m_gldata.VBO);

    m_glFuns->glBindVertexArray(m_gldata.VAO);
    m_glFuns->glBindBuffer(GL_ARRAY_BUFFER, m_gldata.VBO);

    m_glFuns->glBufferData(GL_ARRAY_BUFFER,sizeof(Data::cubeVertices),&Data::cubeVertices[0], GL_STATIC_DRAW);

    m_glFuns->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    m_glFuns->glEnableVertexAttribArray(0);
    m_glFuns->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(sizeof(float)*3));
    m_glFuns->glEnableVertexAttribArray(1);

    m_glFuns->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(sizeof(float)*6));
    m_glFuns->glEnableVertexAttribArray(2);





    m_glFuns->glBindVertexArray(0);

    //new QOpenGLTexture(QImage(":/iamge/container2.png").mirrored());
    m_diffuse=new QOpenGLTexture(QImage(":/iamge/container2.png").mirrored());
    m_specular=new QOpenGLTexture(QImage(":/iamge/container2_specular.png").mirrored());
    textureWall=new QOpenGLTexture(QImage(":/iamge/wall.jpg").mirrored());
}

void CubeActor::Draw()
{

}
