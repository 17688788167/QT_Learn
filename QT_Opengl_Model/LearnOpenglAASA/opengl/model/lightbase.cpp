#include "lightbase.h"
#include<QDebug>

LightBase::LightBase(QOpenGLFunctions_3_3_Core *glfun, const QVector3D &light)
{
        m_glFuns=glfun;
        m_lightColor=light;
        setupMesh();

}

void LightBase::Draw(QOpenGLShaderProgram &shader)
{
        shader.setUniformValue("lightColor",m_lightColor);
        m_glFuns->glBindVertexArray(m_gldata.VAO);

        m_glFuns->glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LightBase::setupMesh()
{
        //创建VBO，VAO，EBO对象,并赋予id
        m_glFuns->glGenVertexArrays(1,&m_gldata.VAO);
        m_glFuns->glGenBuffers(1, &m_gldata.VBO);

        m_glFuns->glBindVertexArray(m_gldata.VAO);
        m_glFuns->glBindBuffer(GL_ARRAY_BUFFER, m_gldata.VBO);

        m_glFuns->glBufferData(GL_ARRAY_BUFFER,sizeof(Data::vertices),NULL, GL_STATIC_DRAW);


//        void *ptr=m_glFuns->glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
//        std::memcpy(ptr,&Data::vertices[0],sizeof(Data::vertices)/2 );
//      //qDebug()<<ptr<<"  sssssss";
//        std::memcpy((int*)ptr+sizeof(Data::vertices)/8,&Data::vertices[sizeof(Data::vertices)/2/sizeof(float)],sizeof(Data::vertices)/2 );
//        m_glFuns->glUnmapBuffer(GL_ARRAY_BUFFER);

        m_glFuns->glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(Data::vertices)/2,&Data::vertices[0]);
        m_glFuns->glBufferSubData(GL_ARRAY_BUFFER,sizeof(Data::vertices)/2,sizeof(Data::vertices)/2,&Data::vertices[sizeof(Data::vertices)/2/sizeof(float)]);

        m_glFuns->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        m_glFuns->glEnableVertexAttribArray(0);

        m_glFuns->glBindVertexArray(0);
}
