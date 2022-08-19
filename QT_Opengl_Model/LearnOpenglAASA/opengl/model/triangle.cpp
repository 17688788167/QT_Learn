#include "triangle.h"
#include "data.h"


void Trianglea::Draw(QOpenGLShaderProgram &shader)
{
    shader.bind();
    m_glFuns->glBindVertexArray(m_gldata.VAO);
    m_glFuns->glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Trianglea::setupMesh()
{
   // m_glFuns->glEnable((GL_PROGRAM_POINT_SIZE));
    //创建VBO，VAO，EBO对象,并赋予id
    m_glFuns->glGenVertexArrays(1,&m_gldata.VAO);
    m_glFuns->glGenBuffers(1, &m_gldata.VBO);

    m_glFuns->glBindVertexArray(m_gldata.VAO);
    m_glFuns->glBindBuffer(GL_ARRAY_BUFFER, m_gldata.VBO);

    m_glFuns->glBufferData(GL_ARRAY_BUFFER,sizeof(Data::quadVertices),&Data::quadVertices[0], GL_STATIC_DRAW);
    //m_glFuns->glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(Data::quadVertices),&Data::quadVertices[0]);

//    m_glFuns->glBufferSubData(GL_ARRAY_BUFFER,sizeof(Data::vertices)/2,sizeof(Data::vertices)/2,&Data::vertices[sizeof(Data::vertices)/2/sizeof(float)]);

     m_glFuns->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
     m_glFuns->glEnableVertexAttribArray(0);
     m_glFuns->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(sizeof(float)*2));

     m_glFuns->glEnableVertexAttribArray(1);

     m_glFuns->glBindVertexArray(0);
}

void Trianglea::Draw()
{

}
